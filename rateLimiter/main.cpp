#include <iostream>
#include <unordered_map>
#include <thread>
#include <chrono>

using namespace std;

enum class RateLimiterType {
    FIXED,
    TOKENBUCKET
};

class RateLimiter {
public:
    virtual ~RateLimiter() = default;
    virtual bool allowRequest(const string &userId) = 0;
};

class RateLimitConfig {
    int maxRequests;
    long timeWindowMillis;
    int bucketSize;
    double refillRate;

public:
    RateLimitConfig(int maxRequests, long timeWindowMillis, int bucketSize, double refillRate)
        : maxRequests(maxRequests), timeWindowMillis(timeWindowMillis),
          bucketSize(bucketSize), refillRate(refillRate) {}

    int getMaxRequests() { 
        return maxRequests; 
    }

    long getTimeWindowMillis() { 
        return timeWindowMillis;
    }
    
    int getBucketSize() { 
        return bucketSize; 
    }
    
    double getRefillRate() { 
        return refillRate; 
    }
};

class UserTokenBucket {
    int tokens;
    long lastRefillTime;

public:
    UserTokenBucket(int tokens, long lastRefillTime)
        : tokens(tokens), lastRefillTime(lastRefillTime) {}

    long getLastRefillTime() { 
        return lastRefillTime; 
    }

    int getTokens() { 
        return tokens; 
    }

    void setTokens(int tokens) { 
        this->tokens = tokens; 
    }

    void setLastRefillTime(long lastRefillTime) { 
        this->lastRefillTime = lastRefillTime; 
    }
};

long getCurrentTimeMillis() {
    return chrono::duration_cast<chrono::milliseconds>(
                chrono::system_clock::now().time_since_epoch())
        .count();
}

class TokenBucketRateLimiter : public RateLimiter {
    RateLimitConfig config;
    unordered_map<string, UserTokenBucket> userBuckets;

public:
    TokenBucketRateLimiter(RateLimitConfig &config) : config(config) {}

    bool allowRequest(const string &userId) override {
        long currentTime = getCurrentTimeMillis();

        if (userBuckets.find(userId) == userBuckets.end()) {
            userBuckets.emplace(userId, UserTokenBucket(config.getBucketSize(), currentTime));
        }

        UserTokenBucket &userBucket = userBuckets.at(userId);

        // Calculate tokens to add based on elapsed time
        long elapsedTime = currentTime - userBucket.getLastRefillTime();
        double tokensToAdd = (elapsedTime / 1000.0) * config.getRefillRate();

        // Only update if we have at least 1 full token to add
        if (tokensToAdd >= 1.0) {
            int fullTokens = (int)(tokensToAdd);
            userBucket.setTokens(min(config.getBucketSize(), userBucket.getTokens() + fullTokens));

            // CRITICAL: Only advance timestamp by the time equivalent
            // to the tokens actually added
            long timeForTokensAdded = (long)((fullTokens / config.getRefillRate()) * 1000.0);
            userBucket.setLastRefillTime(userBucket.getLastRefillTime() + timeForTokensAdded);
        }

        // Check if we have at least 1 token available
        if (userBucket.getTokens() >= 1) {
            userBucket.setTokens(userBucket.getTokens() - 1);
            return true;
        }

        return false;
    }
};

class FixedWindowRateLimiter : public RateLimiter {
    unordered_map<string, int> userRequestCount;
    unordered_map<string, long> userWindowStart;
    RateLimitConfig config;

public:
    FixedWindowRateLimiter(RateLimitConfig &config) : config(config) {}

    bool allowRequest(const string &userId) override {
        long currentTime = getCurrentTimeMillis();

        // Check if user has an existing window
        if (userWindowStart.find(userId) == userWindowStart.end()) {
            // New user - initialize window
            userWindowStart[userId] = currentTime;
            userRequestCount[userId] = 1;
            return true;
        }

        long windowStart = userWindowStart[userId];

        // Check if current window has expired
        if (currentTime - windowStart >= config.getTimeWindowMillis()) {
            // Window expired - start new window
            userWindowStart[userId] = currentTime;
            userRequestCount[userId] = 1;
            return true;
        }

        // Within current window - increment and check limit
        userRequestCount[userId]++;
        return userRequestCount[userId] <= config.getMaxRequests();
    }
};

class RateLimiterFactory {
public:
    static RateLimiter *getRateLimiter(RateLimiterType rateLimiterType, RateLimitConfig &config) {
        switch (rateLimiterType) {
            case RateLimiterType::TOKENBUCKET:
                return new TokenBucketRateLimiter(config);
            case RateLimiterType::FIXED:
                return new FixedWindowRateLimiter(config);
            default:
                throw invalid_argument("Not implemented");
        }
    }
};

void testTokenBucketRateLimiter(RateLimiter *rateLimiter, const string &userId, int bucketSize, double refillRate) {
    cout << "Testing Token Bucket Rate Limiter for user: " << userId << endl;
    cout << "Bucket Size : " << bucketSize << " & Refill Rate : " << refillRate << endl;
    cout << "Making 10 requests..." << endl;

    for (int i = 1; i <= 10; i++) {
        bool allowed = rateLimiter->allowRequest(userId);
        cout << "Request " << i << ": " << (allowed ? "ALLOWED" : "DENIED") << endl;

        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "Test complete. See above for request results and token bucket state after each request." << endl;
}

void testFixedWindowRateLimiter(RateLimiter *rateLimiter, const string &userId, long timeWindowMillis, int maxRequests) {
    cout << "Testing Fixed Window Rate Limiter for user: " << userId << endl;
    cout << "Time Window in Millis : " << timeWindowMillis << " & Max Requests : " << maxRequests << endl;
    cout << "Making 10 requests..." << endl;

    for (int i = 1; i <= 10; i++) {
        bool allowed = rateLimiter->allowRequest(userId);
        cout << "Request " << i << ": " << (allowed ? "ALLOWED" : "DENIED") << endl;

        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "Test complete. See above for request results and window state after each request." << endl;
}

int main() {
    cout << "Rate Limiter Demo" << endl;

    int maxRequests = 2;
    long timeWindowMillis = 4000; // 10 seconds
    double refillRate = 1.0;      // 1 token per second
    int bucketSize = 2;

    RateLimitConfig config(maxRequests, timeWindowMillis, bucketSize, refillRate);

    // bucketSize & refillRate
    RateLimiter *tokenBucket = RateLimiterFactory::getRateLimiter(RateLimiterType::TOKENBUCKET, config);

    // timeWindowMillis & maxRequests
    RateLimiter *fixedWindowBucket = RateLimiterFactory::getRateLimiter(RateLimiterType::FIXED, config);

    testTokenBucketRateLimiter(tokenBucket, "leo_messi", bucketSize, refillRate);
    testFixedWindowRateLimiter(fixedWindowBucket, "cr7", timeWindowMillis, maxRequests);

    delete tokenBucket;
    delete fixedWindowBucket;

    return 0;
}