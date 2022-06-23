#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BqException.h"
#ifndef _BQ_ARRAY_H
#define _BQ_ARRAY_H
namespace bq{
	template <typename T>
	class BqArray {

	public:
		// 构造函数，初始容量16
		BqArray(int capacity = 16) :capacity(capacity), buffer(new T[capacity]), size(0) {
		}
		// 析构函数
		~BqArray() {
			delete [] this->buffer;
		}
	public:
		int capacity; // 容量
		int size; // 大小
		int* buffer; // 数据buffer
		const int loadFactor = 1.5; // 扩容的倍数，默认1.5倍
	public:
		/* 放入元素 */
		void Push(double value) {
			// 达到最大容量，扩容
			if (this->size >= this->capacity) {
				Resize();
			}
			this->buffer[size] = value;
			this->size++;
		}
		
		int GetSize() {
			return this->size;
		}
		int GetCapacity() {
			return this->capacity;
		}
		bool Contains(T o) {
			return indexOf(o) >= 0;
		}
		/*返回包含元素的索引，不存在返回-1*/
		int indexOf(T o) {
			for (int i = 0; i < this->size; i++) {
				if (this->buffer[i] == o) {
					return i;
				}
			}
			return -1;
		}
		bool isEmpty() {
			return size == 0;
		}

		T get(int index) {
			checkIndex(index);
			return buffer[index];
		}
	private:
		/* 扩容 */
		void Resize() {
			int newCapacity = this->capacity * this->loadFactor;
			T* copyBuffer = new T[newCapacity];
			memcpy(copyBuffer, this->buffer, this->capacity * sizeof(T));
			delete[] this->buffer;
			this->capacity = newCapacity;
			this->buffer = copyBuffer;
		}
		int checkIndex(int index) {
			if (index < 0 || index >= size)
				throw BqException(10001,"Index Out of Bounds");
			return index;
		}
	public:
		/*重载[]操作符*/
		T& operator [] (int index) {
			// 下标越界
			if (index > this->size) {
				throw BqException(10001, "Index Out of Bounds");
			}
			return this->buffer[index];
		}
	};
}
#endif