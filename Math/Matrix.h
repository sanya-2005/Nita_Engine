#pragma once
#include "Vector.h"

namespace Math
{
	/// <summary>
	/// Матрица структуры "row-major"
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="rows"></typeparam>
	/// <typeparam name="columns"></typeparam>
	template<typename T, int columns, int rows>
	struct Matrix
	{
	private:
		using MatRow = Vector<T, columns>;
		MatRow data[rows];

	public:
        Matrix()
        {

        }

		/// <summary>
		/// Возвращает индекс СТРОКИ (следовательно, доступ осуществляется по схеме (строка->колонка)
		/// </summary>
		MatRow& operator[](int index)
		{
			return data[index];
		}

		T* Pointer()
		{
			return data[0].Pointer();
		}

        int ColumnsCount()
        {
            return columns;
        }

        int RowsCount()
        {
            return rows;
        }
	};

    using Matrix4f = Matrix<float, 4, 4>;
}