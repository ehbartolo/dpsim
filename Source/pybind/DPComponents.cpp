/* Copyright 2017-2020 Institute for Automation of Complex Power Systems,
 *                     EONERC, RWTH Aachen University
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *********************************************************************************/

#include <DPComponents.h>

namespace py = pybind11;
using namespace pybind11::literals;

void addDPComponents(py::module_ mDP) {

	py::module mDPPh1 = mDP.def_submodule("ph1", "single phase dynamic phasor models");

    py::class_<CPS::DP::SimNode, std::shared_ptr<CPS::DP::SimNode>, CPS::TopologicalNode>(mDP, "SimNode", py::module_local())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::PhaseType>())
		.def(py::init<std::string, CPS::PhaseType, const std::vector<CPS::Complex>>())
		.def("set_initial_voltage", py::overload_cast<CPS::MatrixComp>(&CPS::DP::SimNode::setInitialVoltage))
		.def("set_initial_voltage", py::overload_cast<CPS::Complex>(&CPS::DP::SimNode::setInitialVoltage))
		.def("set_initial_voltage", py::overload_cast<CPS::Complex, int>(&CPS::DP::SimNode::setInitialVoltage))
		.def("single_voltage", &CPS::DP::SimNode::singleVoltage, "phase_type"_a=CPS::PhaseType::Single)
		.def_readonly_static("gnd", &CPS::DP::SimNode::GND);

	py::class_<CPS::DP::Ph1::VoltageSource, std::shared_ptr<CPS::DP::Ph1::VoltageSource>, CPS::SimPowerComp<CPS::Complex>>(mDPPh1, "VoltageSource", py::multiple_inheritance())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::Logger::Level>())
        .def("set_parameters", &CPS::DP::Ph1::VoltageSource::setParameters, "V_ref"_a, "f_src"_a=-1)
		.def("connect", &CPS::DP::Ph1::VoltageSource::connect)
		.def_property("V_ref", createAttributeGetter<CPS::Complex>("V_ref"), createAttributeSetter<CPS::Complex>("V_ref"))
		.def_property("f_src", createAttributeGetter<CPS::Real>("f_src"), createAttributeSetter<CPS::Real>("f_src"));

	py::class_<CPS::DP::Ph1::CurrentSource, std::shared_ptr<CPS::DP::Ph1::CurrentSource>, CPS::SimPowerComp<CPS::Complex>>(mDPPh1, "CurrentSource", py::multiple_inheritance())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::Logger::Level>())
        .def("set_parameters", &CPS::DP::Ph1::CurrentSource::setParameters, "I_ref"_a)
		.def("connect", &CPS::DP::Ph1::CurrentSource::connect)
		.def_property("I_ref", createAttributeGetter<CPS::Complex>("I_ref"), createAttributeSetter<CPS::Complex>("I_ref"));

	py::class_<CPS::DP::Ph1::Resistor, std::shared_ptr<CPS::DP::Ph1::Resistor>, CPS::SimPowerComp<CPS::Complex>>(mDPPh1, "Resistor", py::multiple_inheritance())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::Logger::Level>())
        .def("set_parameters", &CPS::DP::Ph1::Resistor::setParameters, "R"_a)
		.def("connect", &CPS::DP::Ph1::Resistor::connect)
		.def_property("R", createAttributeGetter<CPS::Real>("R"), createAttributeSetter<CPS::Real>("R"));

	py::class_<CPS::DP::Ph1::Capacitor, std::shared_ptr<CPS::DP::Ph1::Capacitor>, CPS::SimPowerComp<CPS::Complex>>(mDPPh1, "Capacitor", py::multiple_inheritance())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::Logger::Level>())
        .def("set_parameters", &CPS::DP::Ph1::Capacitor::setParameters, "C"_a)
		.def("connect", &CPS::DP::Ph1::Capacitor::connect)
		.def_property("C", createAttributeGetter<CPS::Real>("C"), createAttributeSetter<CPS::Real>("C"));

	py::class_<CPS::DP::Ph1::Inductor, std::shared_ptr<CPS::DP::Ph1::Inductor>, CPS::SimPowerComp<CPS::Complex>>(mDPPh1, "Inductor", py::multiple_inheritance())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::Logger::Level>())
        .def("set_parameters", &CPS::DP::Ph1::Inductor::setParameters, "L"_a)
		.def("connect", &CPS::DP::Ph1::Inductor::connect)
		.def_property("L", createAttributeGetter<CPS::Real>("L"), createAttributeSetter<CPS::Real>("L"));

	py::class_<CPS::DP::Ph1::NetworkInjection, std::shared_ptr<CPS::DP::Ph1::NetworkInjection>, CPS::SimPowerComp<CPS::Complex>>(mDPPh1, "NetworkInjection", py::multiple_inheritance())
        .def(py::init<std::string, CPS::Logger::Level>(), "name"_a, "loglevel"_a = CPS::Logger::Level::off)
		.def("set_parameters", &CPS::DP::Ph1::NetworkInjection::setParameters, "V_ref"_a, "f_src"_a = -1)
		.def("connect", &CPS::DP::Ph1::NetworkInjection::connect);

	py::class_<CPS::DP::Ph1::PiLine, std::shared_ptr<CPS::DP::Ph1::PiLine>, CPS::SimPowerComp<CPS::Complex>>(mDPPh1, "PiLine", py::multiple_inheritance())
        .def(py::init<std::string, CPS::Logger::Level>(), "name"_a, "loglevel"_a = CPS::Logger::Level::off)
        .def("set_parameters", &CPS::DP::Ph1::PiLine::setParameters, "series_resistance"_a, "series_inductance"_a, "parallel_capacitance"_a=0, "parallel_conductance"_a=0)
		.def("connect", &CPS::DP::Ph1::PiLine::connect);

	py::class_<CPS::DP::Ph1::RXLoad, std::shared_ptr<CPS::DP::Ph1::RXLoad>, CPS::SimPowerComp<CPS::Complex>>(mDPPh1, "RXLoad", py::multiple_inheritance())
        .def(py::init<std::string, CPS::Logger::Level>(), "name"_a, "loglevel"_a = CPS::Logger::Level::off)
        .def("set_parameters", &CPS::DP::Ph1::RXLoad::setParameters, "active_power"_a, "reactive_power"_a, "volt"_a)
		.def("connect", &CPS::DP::Ph1::RXLoad::connect);

	py::class_<CPS::DP::Ph1::Switch, std::shared_ptr<CPS::DP::Ph1::Switch>, CPS::SimPowerComp<CPS::Complex>>(mDPPh1, "Switch", py::multiple_inheritance())
        .def(py::init<std::string, CPS::Logger::Level>(), "name"_a, "loglevel"_a = CPS::Logger::Level::off)
        .def("set_parameters", &CPS::DP::Ph1::Switch::setParameters, "open_resistance"_a, "closed_resistance"_a, "closed"_a = false)
		.def("open", &CPS::DP::Ph1::Switch::open)
		.def("close", &CPS::DP::Ph1::Switch::close)
		.def("connect", &CPS::DP::Ph1::Switch::connect);

	py::class_<CPS::DP::Ph1::varResSwitch, std::shared_ptr<CPS::DP::Ph1::varResSwitch>, CPS::SimPowerComp<CPS::Complex>>(mDPPh1, "varResSwitch", py::multiple_inheritance())
        .def(py::init<std::string, CPS::Logger::Level>(), "name"_a, "loglevel"_a = CPS::Logger::Level::off)
        .def("set_parameters", &CPS::DP::Ph1::varResSwitch::setParameters, "open_resistance"_a, "closed_resistance"_a, "closed"_a = false)
		.def("open", &CPS::DP::Ph1::varResSwitch::open)
		.def("close", &CPS::DP::Ph1::varResSwitch::close)
		.def("set_init_parameters", &CPS::DP::Ph1::varResSwitch::setInitParameters, "time_step"_a)
		.def("connect", &CPS::DP::Ph1::varResSwitch::connect);

	py::class_<CPS::DP::Ph1::SynchronGeneratorTrStab, std::shared_ptr<CPS::DP::Ph1::SynchronGeneratorTrStab>, CPS::SimPowerComp<CPS::Complex>>(mDPPh1, "SynchronGeneratorTrStab", py::multiple_inheritance())
        .def(py::init<std::string, CPS::Logger::Level>(), "name"_a, "loglevel"_a = CPS::Logger::Level::off)
		.def("set_standard_parameters_PU", &CPS::DP::Ph1::SynchronGeneratorTrStab::setStandardParametersPU,
				"nom_power"_a, "nom_volt"_a, "nom_freq"_a, "Xpd"_a, "inertia"_a, "Rs"_a=0, "D"_a=0)
		.def("set_initial_values", &CPS::DP::Ph1::SynchronGeneratorTrStab::setInitialValues, "elec_power"_a, "mech_power"_a)
		.def("connect", &CPS::DP::Ph1::SynchronGeneratorTrStab::connect);
}
