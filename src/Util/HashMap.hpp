/*
 * HashMap.hpp
 *
 *  Created on: 18 Nov 2013
 *      Author: blake
 */

#ifndef HASHMAP_HPP_
#define HASHMAP_HPP_
#include <string>

namespace HashMapUtils {

/**
 * The class that builds the linked list in each hasmap bucket.
 */

template<class T>
class HashItemLink {
private:

	std::string name_;
	T data_;
	HashItemLink<T>* next_;

public:

	HashItemLink(std::string name, T data) {
		name_ = name;
		data_ = data;
		next_ = 0;
	}

	std::string const& getName() const {
		return name_;
	}

	T getData() const {
		return data_;
	}

	void setData(T data) {
		data_ = data;
	}

	HashItemLink<T>* getNext() const {
		return next_;
	}

	void setNext(HashItemLink<T>* next) {
		next_ = next;
	}

};

/**
 * The bucket class stores a linked list of things if the bucket is not empty
 */

template<class T>
class HashBucket {
private:
	HashItemLink<T>* root_;

public:

	HashBucket() :
			root_(nullptr) {
	}

	bool strEqual(std::string const& left, std::string const& right) const {
		return left.compare(right) == 0;
	}

	HashItemLink<T>* find(std::string const& id) const {

		if (root_ == nullptr) {
			return nullptr;
		}

		HashItemLink<T>* iter = root_;

		while (iter != nullptr) {

			if (strEqual(iter->getName(), id)) {
				return iter;
			}

			iter = iter->getNext();
		}

		return nullptr;
	}

	void remove(std::string const& id) {

		HashItemLink<T>* iter = root_;

		if (strEqual(iter->getName(), iter->name_)) {
			root_ = root_->getNext();
			delete iter;
			return;
		}

		while (iter->getNext() != nullptr) {

			if (strEqual(iter->getNext()->getName(), id)) {
				HashItemLink<T>* str = iter->getNext();
				iter->setNext(str->getNext());
				delete str;
				return;
			}

			iter = iter->getNext();
		}

	}

	void insert(std::string const& id, T data) {

		//printf("Inserting %s\n", id.c_str());

		//If there is no existing list then make one.
		if (root_ == nullptr) {
			root_ = new HashItemLink<T>(id, data);
			//printf("Made %li next %li\n", root_, root_->getNext());
			return;
		}

		//Iterate through all existing nodes. if it is the node we are looking to add then change it instead of inserting it.
		HashItemLink<T>* iter = root_;

		while (iter->getNext() != nullptr) {

			if (strEqual(iter->getName(), id)) {
				iter->setData(data);
				return;
			}

			//printf("Iter %li next %li\n", iter, iter->getNext());

			iter = iter->getNext();
		}

		//One last check to check the last element isn't the target
		if (strEqual(iter->getName(), id)) {
			iter->setData(data);
			return;
		}

		//Set the new end of the list
		iter->setNext(new HashItemLink<T>(id, data));
	}

};

}

const static unsigned int numBucketsDefault = 128;

template<class T>
class HashMap {
private:
	HashMapUtils::HashBucket<T>* buckets_;
	int numBuckets_;

public:

	HashMap() :
			numBuckets_(numBucketsDefault) {
		buckets_ = new HashMapUtils::HashBucket<T>[numBuckets_];
	}

	HashMap(int numBuckets) :
			numBuckets_(numBuckets) {
		buckets_ = new HashMapUtils::HashBucket<T>[numBuckets_];
	}

	virtual ~HashMap() {
	}

	void insert(std::string const& id, T data) {
		buckets_[hash(id)].insert(id, data);
	}

	void remove(std::string const& id) {
		buckets_[hash(id)].remove(id);
	}

	bool exists(std::string const& id) {

		if (buckets_[hash(id)].find(id) != nullptr) {
			return true;
		}

		return false;
	}

	HashMapUtils::HashItemLink<T>* get(std::string id) {
		return buckets_[hash(id)].find(id);
	}

	T find(std::string const& id) {
		HashMapUtils::HashItemLink<T>* linked = get(id);

		if (linked != nullptr) {
			return linked->getData();
		}

		return T();
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
