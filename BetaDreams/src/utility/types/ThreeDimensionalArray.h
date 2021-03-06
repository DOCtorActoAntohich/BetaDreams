// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_UTILITY_TYPES_THREE_DIMENSIONAL_ARRAY_H_INCLUDED
#define BETA_UTILITY_TYPES_THREE_DIMENSIONAL_ARRAY_H_INCLUDED

#include <array>
#include <stdexcept>
#include <sstream>

namespace beta::utility::types {
	/**
	 * Simple 3-dimensional array. Iteration order is YZX.
	 * \tparam Ty A type to store.
	 * \tparam X_SIZE X size of the container.
	 * \tparam Y_SIZE Y size of the container.
	 * \tparam Z_SIZE Z size of the container.
	 */
	template<class Ty, uint32_t X_SIZE, uint32_t Y_SIZE, uint32_t Z_SIZE>
	class ThreeDimensionalArray {
	public:
		using value_type = Ty;
		using const_value_type = const value_type;
		using reference_type = value_type&;
		using const_reference_type = const value_type&;
		using value_type_ptr = value_type*;


		ThreeDimensionalArray() : m_container()
		{	}



		reference_type at(uint32_t x, uint32_t y, uint32_t z) {
			validateIndexes(x, y, z);
			auto index = (y * Z_SIZE + z) * X_SIZE + x;
			return m_container[index];
		}

		const_reference_type at(const uint32_t x, const uint32_t y, const uint32_t z) const {
			validateIndexes(x, y, z);
			auto index = (y * Z_SIZE + z) * X_SIZE + x;
			return m_container[index];
		}

		constexpr value_type_ptr data() const noexcept {
			return m_container.data();
		}



		constexpr uint32_t xSize() const noexcept {
			return X_SIZE;
		}

		constexpr uint32_t ySize() const noexcept {
			return Y_SIZE;
		}

		constexpr uint32_t zSize() const noexcept {
			return Z_SIZE;
		}

		constexpr uint32_t maxElements() const noexcept {
			return CONTAINER_SIZE;
		}



	private:

		void validateIndexes(const uint32_t& x, const uint32_t& y, const uint32_t& z) const {
			static auto check = [](const uint32_t& index, const uint32_t& MAX) {
				if (index >= MAX) {
					std::stringstream ss;
					ss << "Index " << index << " is out of range (" << MAX << ")";
					throw std::out_of_range(ss.str());
				}
			};
			check(x, X_SIZE);
			check(y, Y_SIZE);
			check(z, Z_SIZE);
		}

		static constexpr uint32_t CONTAINER_SIZE = X_SIZE * Y_SIZE * Z_SIZE;
		std::array<value_type, CONTAINER_SIZE> m_container;
	};
}

#endif // !BETA_UTILITY_TYPES_THREE_DIMENSIONAL_ARRAY_H_INCLUDED