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
		// ���캯������ʼ����16
		BqArray(int capacity = 16) :capacity(capacity), buffer(new T[capacity]), size(0) {
		}
		// ��������
		~BqArray() {
			delete [] this->buffer;
		}
	public:
		int capacity; // ����
		int size; // ��С
		int* buffer; // ����buffer
		const int loadFactor = 1.5; // ���ݵı�����Ĭ��1.5��
	public:
		/* ����Ԫ�� */
		void Push(double value) {
			// �ﵽ�������������
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
		/*���ذ���Ԫ�ص������������ڷ���-1*/
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
		/* ���� */
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
		/*����[]������*/
		T& operator [] (int index) {
			// �±�Խ��
			if (index > this->size) {
				throw BqException(10001, "Index Out of Bounds");
			}
			return this->buffer[index];
		}
	};
}
#endif