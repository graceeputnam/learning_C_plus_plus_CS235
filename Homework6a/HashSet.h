#pragma once

#include <vector>
#include <list>
#include <functional>

template<class T>
class HashSet {
public:
    HashSet() {
        bucketCount = 8;
        buckets.resize(bucketCount);
        itemCount = 0;
    }

    ~HashSet() {
    }

    bool insert(T item) {
        if (contains(item)) {
            return false;
        }

        double loadFactor = 0.0;
        if (bucketCount > 0) {
            loadFactor = (double)itemCount / (double)bucketCount;
        }
        if (loadFactor > 0.75) {
            rehash(bucketCount * 2);
        }

        std::size_t hashcode = std::hash<T>{}(item);
        std::size_t index = hashcode % bucketCount;

        buckets[index].push_back(item);
        itemCount++;

        return true;
    }

    bool remove(T item) {
        std::size_t hashcode = std::hash<T>{}(item);
        std::size_t index = hashcode % bucketCount;

        std::list<T> &bucket = buckets[index];
        for (typename std::list<T>::iterator it = bucket.begin();
             it != bucket.end(); ++it) {
            if (*it == item) {
                bucket.erase(it);
                itemCount--;
                return true;
            }
        }
        return false;
    }

    bool contains(T item) const {
        std::size_t hashcode = std::hash<T>{}(item);
        std::size_t index = hashcode % bucketCount;

        const std::list<T> &bucket = buckets[index];
        for (typename std::list<T>::const_iterator it = bucket.begin();
             it != bucket.end(); ++it) {
            if (*it == item) {
                return true;
            }
        }
        return false;
    }

    void clear() {
        for (std::size_t i = 0; i < bucketCount; i++) {
            buckets[i].clear();
        }
        itemCount = 0;
    }

    int size() const {
        return itemCount;
    }

private:
    std::vector<std::list<T>> buckets;
    std::size_t bucketCount;
    int itemCount;

    void rehash(std::size_t newBucketCount) {
        std::vector<std::list<T>> newBuckets;
        newBuckets.resize(newBucketCount);

        for (std::size_t i = 0; i < bucketCount; i++) {
            std::list<T> &bucket = buckets[i];
            for (typename std::list<T>::iterator it = bucket.begin();
                 it != bucket.end(); ++it) {
                T item = *it;
                std::size_t hashcode = std::hash<T>{}(item);
                std::size_t newIndex = hashcode % newBucketCount;
                newBuckets[newIndex].push_back(item);
            }
        }

        buckets = newBuckets;
        bucketCount = newBucketCount;
    }
};
