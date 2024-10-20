#pragma once

namespace Math
{
	template<typename T, int size>
	struct Vector
	{
	private:
		T data[size];

	public:
        Vector()
        {
            for (int i = 0; i < size; i++)
            {
                data[i] = T();
            }
        }

		T& operator[](int index)
		{
			return data[index];
		}

        Vector<T, size>& operator*(Vector<T, size>& value)
        {
            for (int i = 0; i < value.Size(); i++)
            {
                data[i] *= value[i];
            }

            return *this;
        }

        Vector<T, size>& operator+(Vector<T, size>& value)
        {
            for (int i = 0; i < value.Size(); i++)
            {
                data[i] += value[i];
            }

            return *this;
        }

        Vector<T, size>& operator=(Vector<T, size>& value)
        {
            for (int i = 0; i < value.Size(); i++)
            {
                data[i] = value[i];
            }

            return *this;
        }

		T* Pointer()
		{
			return data;
		}

        int Size()
        {
            return size;
        }
	};

    using Vector4f = Vector<float, 4>;
	using Vector3f = Vector<float, 3>;
    using Vector2f = Vector<float, 2>;
}

