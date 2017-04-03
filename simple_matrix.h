#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>
#if defined(DEBUG) || defined(QT_DEBUG) || defined(QT_QML_DEBUG)
#include <iostream>
#include <assert.h>
#endif

template<unsigned int length, typename num = double>
class lineVector
{
	num val[length];
public:
	lineVector() {}
	lineVector(std::initializer_list<num> init) {
#if defined(DEBUG) || defined(QT_DEBUG) || defined(QT_QML_DEBUG)
		if (init.size() != length) std::cerr << "Warning: Initialiser list of wrong width/length" << std::endl;
#endif
		std::copy(init.begin(), init.end(), val);
	}
	unsigned int getLength() { return length; }
	num& operator[] (unsigned int index) {
#if defined(DEBUG) || defined(QT_DEBUG) || defined(QT_QML_DEBUG)
		if (index >= length) std::cerr << "Warning: accessing behind the end of vector " << index << "/" << length << std::endl;
#endif
		return val[index];
	}
	const num& operator[] (unsigned int index) const {
#if defined(DEBUG) || defined(QT_DEBUG) || defined(QT_QML_DEBUG)
		if (index >= length) std::cerr << "Warning: reading behind the end of vector " << index << "/" << length << std::endl;
#endif
		return val[index];
	}
	lineVector<length, num> operator+ (const lineVector<length, num>& other) {
		lineVector<length, num> result;
		for (unsigned int i = 0; i < length; i++) result.val[i] = val[i] + other.val[i];
		return result;
	}
	lineVector<length, num> operator+= (const lineVector<length, num>& other) {
		for (unsigned int i = 0; i < length; i++) val[i] += other.val[i];
		return *this;
	}
	lineVector<length, num> operator- (const lineVector<length, num>& other) {
		lineVector<length, num> result;
		for (unsigned int i = 0; i < length; i++) result.val[i] = val[i] - other.val[i];
		return result;
	}
	lineVector<length, num> operator-= (const lineVector<length, num>& other) {
		for (unsigned int i = 0; i < length; i++) val[i] -= other.val[i];
		return *this;
	}
	lineVector<length, num> operator* (num other) {
		lineVector<length, num> result;
		for (unsigned int i = 0; i < length; i++) result.val[i] = val[i] * other;
		return result;
	}
	lineVector<length, num> operator-= (num other) {
		for (unsigned int i = 0; i < length; i++) val[i] *= other;
		return *this;
	}
	num operator*(const lineVector<length, num>& other) {
		num result = 0;
		for (unsigned int i = 0; i < length; i++) result +=  val[i] * other[i];
	}
	bool operator== (const lineVector<length, num>& other) {
		for (unsigned int i = 0; i < length; i++)
				if (val[i] != other[i]) return false;
		return true;
	}
	bool operator!= (const lineVector<length, num>& other) {
		return !(*this == other);
	}
	template<unsigned int lengthf, typename numf>
	friend std::ostream& operator<<(std::ostream& out, const lineVector<lengthf, numf>& vec);
};

template<unsigned int length, typename num = double>
std::ostream& operator<<(std::ostream& out, const lineVector<length, num>& vec)
{
	out << "(";
	if (length) out << vec.val[0];
	for (unsigned int i = 1; i < length; i++) out << ", " << vec.val[i];
	return out << ")";
}

template<unsigned int height, unsigned int width, typename num = double>
class matrix
{
	lineVector<width, num> val[height];
public:
	matrix() {}
	matrix(std::initializer_list<std::initializer_list<num>> init) {
#if defined(DEBUG) || defined(QT_DEBUG) || defined(QT_QML_DEBUG)
		if (init.size() != height) std::cerr << "Warning: Initialiser list of wrong height" << std::endl;
#endif
		std::copy(init.begin(), init.end(), val);
	}
	unsigned int getHeight() { return height; }
	unsigned int getWidth() { return width; }
	lineVector<width, num>& operator[] (unsigned int index) {
#if defined(DEBUG) || defined(QT_DEBUG) || defined(QT_QML_DEBUG)
		if (index >= height) std::cerr << "Warning: accessing behind the end of matrix" << std::endl;
#endif
		return val[index];
	}
	const lineVector<width, num>& operator[] (unsigned int index) const {
#if defined(DEBUG) || defined(QT_DEBUG) || defined(QT_QML_DEBUG)
		if (index >= height) std::cerr << "Warning: reading behind the end of matrix" << std::endl;
#endif
		return val[index];
	}
	matrix<height, width, num> operator+ (const matrix<height, width, num>& other) {
		matrix<height, width, num> result;
		for (unsigned int i = 0; i < height; i++) result[i] = val[i] + other[i];
		return result;
	}
	matrix<height, width, num> operator+= (const matrix<height, width, num>& other) {
		for (unsigned int i = 0; i < height; i++) val[i] += other[i];
		return *this;
	}
	matrix<height, width, num> operator- (const matrix<height, width, num>& other) {
		matrix<height, width, num> result;
		for (unsigned int i = 0; i < height; i++) result[i] = val[i] - other[i];
		return result;
	}
	matrix<height, width, num> operator-= (const matrix<height, width, num>& other) {
		for (unsigned int i = 0; i < height; i++) val[i] -= other[i];
		return *this;
	}
	template<unsigned int otherWidth>
	matrix<height, otherWidth, num> operator* (const matrix<width, otherWidth, num>& other) {
		matrix<height, otherWidth, num> result;
		for (unsigned int i = 0; i < height; i++)
			for (unsigned int j = 0; j < otherWidth; j++) {
				result[i][j] = 0;
				for (unsigned int k = 0; k < width; k++)
					result[i][j] += val[i][k] * other[k][j];
			}
		return result;
	}
	matrix<height, width, num> operator* (num other) {
		matrix<height, width, num> result;
		for (unsigned int i = 0; i < height; i++)
			for (unsigned int j = 0; j < width; j++)
				result[i][j] = val[i][j] * other;
		return result;
	}
	matrix<height, width, num> operator*= (num other) {
		for (unsigned int i = 0; i < height; i++)
			for (unsigned int j = 0; j < width; j++)
				val[i][j] *= other;
		return *this;
	}
	bool operator== (const matrix<height, width, num>& other) {
		for (unsigned int i = 0; i < height; i++)
			for (unsigned int j = 0; j < width; j++)
				if (val[i][j] != other[i][j]) return false;
		return true;
	}
	bool operator!= (const matrix<height, width, num>& other) {
		return !(*this == other);
	}
	template<unsigned int heightf, unsigned int widthf, typename numf>
	friend std::ostream& operator<<(std::ostream& out, matrix<heightf, widthf, numf> mat);
};

template<unsigned int height, unsigned int width, typename num = double>
std::ostream& operator<<(std::ostream& out, matrix<height, width, num> mat)
{
	out << "matrix:" << std::endl;
	for (unsigned int i = 0; i < height; i++) out << mat.val[i] << std::endl;
	return out;
}

template<unsigned int height, unsigned int width, typename num = double>
lineVector<width, num> operator* (lineVector<height, num> vec, matrix<height, width, num> mat) {
	lineVector<width, num> result;
	for (unsigned int i = 0; i < width; i++) {
		result[i] = 0;
		for (unsigned int j = 0; j < height; j++)
			result[i] += vec[j] * mat[j][i];
	}
	return result;
}

template<unsigned int height, unsigned int width, typename num = double>
matrix<height, width, num> operator* (matrix<height, 1, num> mat, lineVector<width, num> vec) {
	matrix<height, width, num> result;
	for (unsigned int i = 0; i < height; i++)
		for (unsigned int j = 0; j < width; j++)
			result[i][j] = mat[i][0] * vec[j];
	return result;
}

template<unsigned int size, typename num = double>
matrix<size, size, num> operator^ (matrix<size, size, num> mat, unsigned int power) {
	matrix<size, size, num> result;
	if (power == 0) {
		for (unsigned int i = 0; i < size; i++)
			for (unsigned int j = 0; j < size; j++)
				result[i][j] = (i == j) ? 1 : 0;
		return result;
	}
	result = mat;
	for (int t = 1; t < power; t++) {
		result *= mat;
	}
	return result;
}

template<unsigned int size, typename num = double>
num determinant(matrix<size, size, num> mat) {
	num result = 0;
	int sign = 1;
	for (int i = 0; i < size; i++) {
		matrix<size - 1, size - 1, num> subMat;
		for (int pos = 0, subPos = -1; pos < size; pos++) {
			if (pos == i) {
				continue;
			} else subPos++;
			for (int k = 1 /*k = 0 is used for the multiplier*/; k < size; k++) {
				subMat[k - 1][subPos] = mat[k][pos];
			}
		}
		result += sign * mat[0][i] * determinant(subMat);
		sign *= -1;
	}
	return result;
}

template<typename num = double>
num determinant(matrix<1, 1, num> mat) {
	return mat[0][0];
}

template<typename num = double>
num determinant(matrix<2, 2, num> mat) {
	return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

template<typename num = double>
num determinant(matrix<3, 3, num> mat) {
	// Rule of Sarrus
	return mat[0][0] * mat[1][1] * mat[2][2] + mat[1][0] * mat[2][1] * mat[0][2] + mat[2][0] * mat[0][1] * mat[1][2]
			- mat[0][2] * mat[1][1] * mat[2][0] - mat[1][2] * mat[2][1] * mat[0][0] - mat[2][2] * mat[0][1] * mat[1][0];
}


template<unsigned int size, typename num = double>
matrix<size, size, num> operator*= (matrix<size, size, num>& changed, const matrix<size, size, num>& other) {
	matrix<size, size, num> result = changed * other;
	changed = result; // Cannot be changed in-situ
	return result;
}

template<unsigned int height, unsigned int width, typename num = double>
matrix<width, height, num> transpose(const matrix<height, width, num>& used) {
	matrix<width, height, num> result;
	for (unsigned int i = 0; i < height; i++)
		for (unsigned int j = 0; j < width; j++)
			result[j][i] = used[i][j];
	return result;
}

template<unsigned int height, typename num = double>
lineVector<height, num> transpose(const matrix<height, 1, num>& used) {
	lineVector<height, num> result;
	for (unsigned int i = 0; i < height; i++)
		result[i] = used[i][0];
	return result;
}

template<unsigned int length, typename num = double>
matrix<length, 1, num> transpose(const lineVector<length, num>& used) {
	matrix<length, 1, num> result;
	for (unsigned int i = 0; i < length; i++)
		result[i][0] = used[i];
	return result;
}

#endif // MATRIX_H
