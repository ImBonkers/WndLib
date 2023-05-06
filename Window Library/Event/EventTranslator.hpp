#pragma once

#include "EventManager.hpp"

#define SINGLETON(type_name) {												\
			type_name(const type_name&) = delete;							\
			void operator=(const type_name&) = delete;						\
			static type_name& get_instance()								\
			{																\
			static type_name instance;										\
			return instance;												\
			}																\
		}


class EventTranslator
{
public:
	void translate()
	{
	}
};