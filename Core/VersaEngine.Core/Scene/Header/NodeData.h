#ifndef NODEDATA_H
#define NODEDATA_H

#include "Node.h"

template <typename T>
void Node::SetInputData(const std::string& pinName, const T& value);

template <typename T>
T Node::GetOutputData(const std::string& pinName) const;

#endif#pragma once
