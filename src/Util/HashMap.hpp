/*
 * HashMap.hpp
 *
 *  Created on: 18 Nov 2013
 *      Author: blake
 */

#ifndef HASHMAP_HPP_
#define HASHMAP_HPP_
#include <string>
#include <vector>

namespace HashMapUtils {

template<class T>
class HashBucket {
  private:
    std::vector<std::pair<std::string, T>> root_;

  public:

    inline bool itemIsNamed(unsigned int i, std::string const& str) const {
        return root_[i].first.compare(str) == 0;
    }

    bool get(std::string const& id, T& target) const {
        for (unsigned int i = 0; i < root_.size(); i++) {
            if (itemIsNamed(i, id)) {
                target = root_[i].second;
                return true;
            }
        }
        return false;
    }

    void remove(std::string const& id) {
        for (unsigned int i = 0; i < root_.size(); i++) {
            if (itemIsNamed(i, id)) {
                root_.erase(root_.begin() + i);
                return;
            }
        }
    }

    void set(std::string const& id, T data) {
        for (unsigned int i = 0; i < root_.size(); i++) {
            if (itemIsNamed(i, id)) {
                root_[i].second = data;
                return;
            }
        }
        root_.push_back(std::pair<std::string, T>(id, data));
    }
};

}

const static unsigned int numBucketsDefault = 128;

template<class T>
class HashMap {
  private:
    HashMapUtils::HashBucket<T>* buckets_;
    unsigned int numBuckets_;

  public:

    HashMap() {
        numBuckets_ = numBucketsDefault;
        buckets_ = new HashMapUtils::HashBucket<T>[numBuckets_];
    }

    HashMap(int numBuckets) {
        numBuckets_ = numBuckets;
        buckets_ = new HashMapUtils::HashBucket<T>[numBuckets_];
    }

    virtual ~HashMap() {
        //delete[] buckets_;
    }

    HashMap<T>& operator=(HashMap<T> const& other) {
        
        if (this != &other) {
            delete[] buckets_;
            numBuckets_ = other.numBuckets_;
            buckets_ = new HashMapUtils::HashBucket<T>[numBuckets_];
            for (unsigned int i = 0; i < numBuckets_; i++) {
                buckets_[i] = other.buckets_[i];
            }
        }

        return *this;
    }

    void set(std::string const& id, T data) {
        buckets_[hash(id)].set(id, data);
    }

    void remove(std::string const& id) {
        buckets_[hash(id)].remove(id);
    }

    bool get(std::string const& id, T& target) {
        return buckets_[hash(id)].get(id, target);
    }

    int hash(std::string const& id) {

        size_t len = id.size();
        uint32_t hash = 0;
        uint32_t i = 0;

        for (hash = i = 0; i < len; ++i) {
            hash += id[i];
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }

        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);

        return hash % numBuckets_;
    }
};

#endif /* HASHMAP_HPP_ */
