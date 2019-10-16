#include "State.h"

#include <fstream>
#include <iomanip> // std::setw

#pragma warning(push) // supressing warnings in external code
#pragma warning( disable : 26451 )
#pragma warning( disable : 26495 )
#pragma warning( disable : 28020 )
#include "json.hpp"
#pragma warning(pop)

static std::string filename = "mcc_state.json";

State read_state_from_disk() {
	std::ifstream i(filename);
	if (!i.good()) {
		return State();
	}
	nlohmann::json j;
	i >> j;
	i.close();
	State s;
	j["gb_hours"].get_to(s.gb_hours);
	j["events"].get_to(s.events);
	return s;
}

void write_state_to_disk(const State& state){
	nlohmann::json j;
	j["gb_hours"] = state.gb_hours;
	j["events"] = state.events;
	std::ofstream o(filename);
	o << std::setw(4) << j << std::endl;
	o.close();
}
