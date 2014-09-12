#ifndef INCLUDE_UI_H
#define INCLUDE_UI_H

#include <iostream>
#include <memory>

namespace ui {



	class option {

		virtual const char* text () const = 0;
		virtual       void  call () const = 0;
	};

	class help : public option {

		const char* text () const { return "?"; }

		void call () const {
			std::cout << "Help me!\n";
		}
	};

	class connect : public option {

		const char* text () const { return "connect"; }
		
		void call () const {
			std::cout << "Help me!\n";
		}
	};

	class quit : public option {

		const char* text () const { return "quit"; }
		
		void call () const {
			std::cout << "Help me!\n";
		}
	};

	class get : public option {

		const char* text () const { return "get"; }
		
		void call () const {
			std::cout << "Help me!\n";
		}
	};



}

#endif