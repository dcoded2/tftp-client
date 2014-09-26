#ifndef INCLUDE_TFTP_UI_TRANSISTION_TABLE_H
#define INCLUDE_TFTP_UI_TRANSISTION_TABLE_H

#include <map>
#include <cstdint>

namespace tftp {
namespace ui   {

static std::map <State, State> next = {
	{State::INIT     , State::PROMPT},
	{State::PROMPT   , State::STDIN },
	{State::STDIN    , State::PARSE },
	{State::NOCMD    , State::PROMPT},
	{State::QUIT     , State::QUIT  },
	{State::HELP     , State::PROMPT},
	{State::CONNECT  , State::PROMPT},
	{State::MODE     , State::PROMPT},
	{State::GET      , State::PROMPT},
	{State::PUT      , State::PROMPT}
};

}
}

#endif