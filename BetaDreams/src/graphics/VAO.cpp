// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "VAO.h"

#include <stdexcept>
#include <sstream>

#include <GL/glew.h>

using namespace beta::graphics;

VAO::VAO() {
	glGenVertexArrays(1, &m_id);
	m_isBound = false;
	m_objects = 0;
}

VAO::VAO(VAO&& other) noexcept {
	*this = std::move(other);
}

VAO::~VAO() noexcept {
	glDeleteVertexArrays(1, &m_id);
}



void VAO::bind() noexcept {
	glBindVertexArray(m_id);
	m_isBound = true;
}

void VAO::unbind() noexcept {
	glBindVertexArray(0);
	m_isBound = false;
}

bool VAO::isBound() const noexcept {
	return m_isBound;
}



VAO& VAO::attach(VBO&& vbo) {
	static constexpr const size_t MAX_VBOS = 16;
	if (m_vbos.size() == MAX_VBOS) {
		std::stringstream ss;
		ss << "Tried to add more than " << MAX_VBOS << " to VAO";
		throw std::overflow_error(ss.str());
	}

	if (m_objects == 0) {
		m_objects = vbo.objects();
	}

	if (m_objects != vbo.objects()) {
		std::stringstream ss;
		ss << "Invalid number of objects in VBO: " << vbo.objects() <<
			  " (must be " << m_objects << ")";
		throw std::invalid_argument(ss.str());
	}

	glBindVertexArray(m_id);

	vbo.bind();

	glVertexAttribPointer(
		m_vbos.size(),			// Attribute list index.
		vbo.objectComponents(),	// How many numbers describe the part of the object.
		GL_FLOAT,				// Bytes per number.
		GL_FALSE,				// Should be normalized?
		0,						// Object size in bytes.
		nullptr					// Offset from the object beginning to describe this part.
	);
	glEnableVertexAttribArray(m_vbos.size());

	vbo.unbind();

	glBindVertexArray(0);

	m_vbos.push_back(std::move(vbo));
	return *this;
}



void VAO::draw() {
	this->bind();
	glDrawArrays(GL_TRIANGLES, 0, m_objects);
	this->unbind();
}



VAO& VAO::operator=(VAO&& other) noexcept {
	if (this == &other) {
		return *this;
	}

	this->m_id = other.m_id;
	this->m_vbos = std::move(other.m_vbos);
	this->m_objects = other.m_objects;
	this->m_isBound = other.m_isBound;

	other.m_id = 0;
	other.m_isBound = false;
	other.m_objects = 0;

	return *this;
}