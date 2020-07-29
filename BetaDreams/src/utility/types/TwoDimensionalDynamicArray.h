// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_UTILITY_TYPES_TWO_DIMENSIONAL_DYNAMIC_ARRAY_H_INCLUDED
#define BETA_UTILITY_TYPES_TWO_DIMENSIONAL_DYNAMIC_ARRAY_H_INCLUDED

#include <cstdint>
#include <sstream>

namespace beta::utility::types {
	/**
	 * Simple 2-dimensional array stored in dynamic memory. Iteration order is YX.
	 * \tparam Ty A type to store.
	 */
	template<class Ty>
	class TwoDimensionalDynamicArray {
	public:
		using value_type = Ty;
		using const_value_type = const value_type;
		using reference_type = value_type&;
		using const_reference_type = const value_type&;
		using value_type_ptr = value_type*;

		TwoDimensionalDynamicArray(uint32_t x, uint32_t y) {
			m_xSize = x;
			m_ySize = y;
			m_containerSize = m_xSize * m_ySize;
			m_container = new value_type[m_containerSize];
			for (uint32_t i = 0; i < m_containerSize; ++i) {
				m_container[i] = value_type();
			}
		}

		~TwoDimensionalDynamicArray() {
			delete[] m_container;
		}

		reference_type at(uint32_t x, uint32_t y) {
			validateIndexes(x, y);
			auto index = y * m_xSize + x;
			return m_container[index];
		}

		const_reference_type at(uint32_t x, uint32_t y) const {
			validateIndexes(x, y);
			auto index = y * m_xSize + x;
			return m_container[index];
		}


		const uint32_t& xSize() const noexcept {
			return m_xSize;
		}

		const uint32_t& ySize() const noexcept {
			return m_ySize;
		}

		constexpr value_type_ptr data() const noexcept {
			return m_container;
		}



	private:

		void validateIndexes(const uint32_t& x, const uint32_t& y) {
			static auto check = [](const uint32_t& index, const uint32_t& max) {
				if (index >= max) {
					std::stringstream ss;
					ss << "Index " << index << " is out of range (" << max << ")";
					throw std::out_of_range(ss.str());
				}
			};
			check(x, m_xSize);
			check(y, m_ySize);
		}

		uint32_t m_xSize = 0;
		uint32_t m_ySize = 0;
		uint32_t m_containerSize = 0;
		value_type_ptr m_container = nullptr;
	};
}

#endif // !BETA_UTILITY_TYPES_TWO_DIMENSIONAL_DYNAMIC_ARRAY_H_INCLUDED