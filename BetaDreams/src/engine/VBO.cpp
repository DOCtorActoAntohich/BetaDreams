// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "VBO.h"

#include <stdexcept>
#include <sstream>

#include <GL/glew.h>

using namespace beta::engine;


VBO::VBO() {
	glGenBuffers(1, &m_id);
	m_objectComponents = 0;
	m_isBound = false;
}

VBO::VBO(const std::vector<float_t>& data, uint32_t objectComponents) : VBO() {
	this->setData(data, objectComponents);
}

VBO::VBO(VBO&& other) noexcept {
	*this = std::move(other);
}

VBO::~VBO() noexcept {
	glDeleteBuffers(1, &m_id);
	m_id = 0;
	m_data.clear();
}



void VBO::bind() noexcept {
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	m_isBound = true;
}

void VBO::unbind() noexcept {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_isBound = false;
}

bool VBO::isBound() const noexcept {
	return m_isBound;
}



uint32_t VBO::objectComponents() const noexcept {
	return m_objectComponents;
}



uint32_t VBO::objects() const noexcept {
	return static_cast<uint32_t>(m_data.size()) / m_objectComponents;
}



void VBO::setData(const std::vector<float_t>& data, uint32_t objectComponents) {
	if (static_cast<uint32_t>(data.size()) % objectComponents != 0) {
		std::stringstream ss;
		ss << "Container of size " << data.size() <<
			" cannot store data for objects with " << objectComponents <<
			" components";
		throw std::invalid_argument(ss.str());
	}

	m_data = data;
	m_objectComponents = objectComponents;

	glBindBuffer(GL_ARRAY_BUFFER, m_id);

	size_t storageSizeBytes = data.size() * sizeof(float_t);
	glBufferData(GL_ARRAY_BUFFER, storageSizeBytes, data.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



VBO& VBO::operator=(VBO&& other) noexcept {
	if (this == &other) {
		return *this;
	}

	this->m_id = other.m_id;
	this->m_objectComponents = other.m_objectComponents;
	this->m_isBound = other.m_isBound;
	this->m_data = other.m_data;

	other.m_id = other.m_objectComponents = 0;
	other.m_isBound = false;
	other.m_data.clear();

	return *this;
}