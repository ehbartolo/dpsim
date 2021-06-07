/* Copyright 2017-2020 Institute for Automation of Complex Power Systems,
 *                     EONERC, RWTH Aachen University
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *********************************************************************************/

#include <EMTComponents.h>

namespace py = pybind11;
using namespace pybind11::literals;

void addEMTComponents(py::module_ mEMT) {
	py::class_<CPS::EMT::SimNode, std::shared_ptr<CPS::EMT::SimNode>, CPS::TopologicalNode>(mEMT, "SimNode", py::module_local())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::PhaseType>())
		.def(py::init<std::string, CPS::PhaseType, const std::vector<CPS::Complex>>())
		.def("set_initial_voltage", py::overload_cast<CPS::MatrixComp>(&CPS::EMT::SimNode::setInitialVoltage))
		.def("set_initial_voltage", py::overload_cast<CPS::Complex>(&CPS::EMT::SimNode::setInitialVoltage))
		.def("set_initial_voltage", py::overload_cast<CPS::Complex, int>(&CPS::EMT::SimNode::setInitialVoltage))
		.def_readonly_static("gnd", &CPS::EMT::SimNode::GND);

	py::module mEMTPh1 = mEMT.def_submodule("ph1", "single phase electromagnetic-transient models");
	addEMTPh1Components(mEMTPh1);
	py::module mEMTPh3 = mEMT.def_submodule("ph3", "three phase electromagnetic-transient models");
	addEMTPh3Components(mEMTPh3);
}

void addEMTPh1Components(py::module_ mEMTPh1) {
	py::class_<CPS::EMT::Ph1::CurrentSource, std::shared_ptr<CPS::EMT::Ph1::CurrentSource>, CPS::SimPowerComp<CPS::Real>>(mEMTPh1, "CurrentSource", py::multiple_inheritance())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::Logger::Level>())
        .def("set_parameters", &CPS::EMT::Ph1::CurrentSource::setParameters, "I_ref"_a, "f_src"_a = -1)
		.def("connect", &CPS::EMT::Ph1::CurrentSource::connect)
		.def_property("I_ref", createAttributeGetter<CPS::Complex>("I_ref"), createAttributeSetter<CPS::Complex>("I_ref"))
		.def_property("f_src", createAttributeGetter<CPS::Real>("f_src"), createAttributeSetter<CPS::Real>("f_src"));

	py::class_<CPS::EMT::Ph1::VoltageSource, std::shared_ptr<CPS::EMT::Ph1::VoltageSource>, CPS::SimPowerComp<CPS::Real>>(mEMTPh1, "VoltageSource", py::multiple_inheritance())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::Logger::Level>())
        .def("set_parameters", &CPS::EMT::Ph1::VoltageSource::setParameters, "V_ref"_a, "f_src"_a = -1)
		.def("connect", &CPS::EMT::Ph1::VoltageSource::connect)
		.def_property("V_ref", createAttributeGetter<CPS::Complex>("V_ref"), createAttributeSetter<CPS::Complex>("V_ref"))
		.def_property("f_src", createAttributeGetter<CPS::Real>("f_src"), createAttributeSetter<CPS::Real>("f_src"));

	py::class_<CPS::EMT::Ph1::Resistor, std::shared_ptr<CPS::EMT::Ph1::Resistor>, CPS::SimPowerComp<CPS::Real>>(mEMTPh1, "Resistor", py::multiple_inheritance())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::Logger::Level>())
        .def("set_parameters", &CPS::EMT::Ph1::Resistor::setParameters, "R"_a)
		.def("connect", &CPS::EMT::Ph1::Resistor::connect)
		.def_property("R", createAttributeGetter<CPS::Real>("R"), createAttributeSetter<CPS::Real>("R"));

	py::class_<CPS::EMT::Ph1::Capacitor, std::shared_ptr<CPS::EMT::Ph1::Capacitor>, CPS::SimPowerComp<CPS::Real>>(mEMTPh1, "Capacitor", py::multiple_inheritance())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::Logger::Level>())
        .def("set_parameters", &CPS::EMT::Ph1::Capacitor::setParameters, "C"_a)
		.def("connect", &CPS::EMT::Ph1::Capacitor::connect)
		.def_property("C", createAttributeGetter<CPS::Real>("C"), createAttributeSetter<CPS::Real>("C"));

	py::class_<CPS::EMT::Ph1::Inductor, std::shared_ptr<CPS::EMT::Ph1::Inductor>, CPS::SimPowerComp<CPS::Real>>(mEMTPh1, "Inductor", py::multiple_inheritance())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::Logger::Level>())
        .def("set_parameters", &CPS::EMT::Ph1::Inductor::setParameters, "L"_a)
		.def("connect", &CPS::EMT::Ph1::Inductor::connect)
		.def_property("L", createAttributeGetter<CPS::Real>("L"), createAttributeSetter<CPS::Real>("L"));

}

void addEMTPh3Components(py::module_ mEMTPh3) {
	py::class_<CPS::EMT::Ph3::VoltageSource, std::shared_ptr<CPS::EMT::Ph3::VoltageSource>, CPS::SimPowerComp<CPS::Real>>(mEMTPh3, "VoltageSource", py::multiple_inheritance())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::Logger::Level>())
        .def("set_parameters", &CPS::EMT::Ph3::VoltageSource::setParameters, "V_ref"_a, "f_src"_a = -1)
		.def("connect", &CPS::EMT::Ph3::VoltageSource::connect)
		.def_property("V_ref", createAttributeGetter<CPS::MatrixComp>("V_ref"), createAttributeSetter<CPS::MatrixComp>("V_ref"))
		.def_property("f_src", createAttributeGetter<CPS::Real>("f_src"), createAttributeSetter<CPS::Real>("f_src"));

	py::class_<CPS::EMT::Ph3::ControlledVoltageSource, std::shared_ptr<CPS::EMT::Ph3::ControlledVoltageSource>, CPS::SimPowerComp<CPS::Real>>(mEMTPh3, "ControlledVoltageSource", py::multiple_inheritance())
		.def(py::init<std::string, CPS::Logger::Level>(), "name"_a, "loglevel"_a = CPS::Logger::Level::off)
        .def("connect", &CPS::EMT::Ph3::ControlledVoltageSource::connect);

	py::class_<CPS::EMT::Ph3::Resistor, std::shared_ptr<CPS::EMT::Ph3::Resistor>, CPS::SimPowerComp<CPS::Real>>(mEMTPh3, "Resistor", py::multiple_inheritance())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::Logger::Level>())
        .def("set_parameters", &CPS::EMT::Ph3::Resistor::setParameters, "R"_a)
		.def("connect", &CPS::EMT::Ph3::Resistor::connect);;

	py::class_<CPS::EMT::Ph3::Capacitor, std::shared_ptr<CPS::EMT::Ph3::Capacitor>, CPS::SimPowerComp<CPS::Real>>(mEMTPh3, "Capacitor", py::multiple_inheritance())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::Logger::Level>())
        .def("set_parameters", &CPS::EMT::Ph3::Capacitor::setParameters, "C"_a)
		.def("connect", &CPS::EMT::Ph3::Capacitor::connect);

	py::class_<CPS::EMT::Ph3::Inductor, std::shared_ptr<CPS::EMT::Ph3::Inductor>, CPS::SimPowerComp<CPS::Real>>(mEMTPh3, "Inductor", py::multiple_inheritance())
        .def(py::init<std::string>())
		.def(py::init<std::string, CPS::Logger::Level>())
        .def("set_parameters", &CPS::EMT::Ph3::Inductor::setParameters, "L"_a)
		.def("connect", &CPS::EMT::Ph3::Inductor::connect);

	py::class_<CPS::EMT::Ph3::NetworkInjection, std::shared_ptr<CPS::EMT::Ph3::NetworkInjection>, CPS::SimPowerComp<CPS::Real>>(mEMTPh3, "NetworkInjection", py::multiple_inheritance())
        .def(py::init<std::string, CPS::Logger::Level>(), "name"_a, "loglevel"_a = CPS::Logger::Level::off)
		.def("set_parameters", &CPS::EMT::Ph3::NetworkInjection::setParameters, "V_ref"_a, "f_src"_a)
		.def("connect", &CPS::EMT::Ph3::NetworkInjection::connect);

	py::class_<CPS::EMT::Ph3::PiLine, std::shared_ptr<CPS::EMT::Ph3::PiLine>, CPS::SimPowerComp<CPS::Real>>(mEMTPh3, "PiLine", py::multiple_inheritance())
        .def(py::init<std::string, CPS::Logger::Level>(), "name"_a, "loglevel"_a = CPS::Logger::Level::off)
        .def("set_parameters", &CPS::EMT::Ph3::PiLine::setParameters, "series_resistance"_a, "series_inductance"_a, "parallel_capacitance"_a=zeroMatrix(3), "parallel_conductance"_a=zeroMatrix(3))
		.def("connect", &CPS::EMT::Ph3::PiLine::connect);

	py::class_<CPS::EMT::Ph3::RXLoad, std::shared_ptr<CPS::EMT::Ph3::RXLoad>, CPS::SimPowerComp<CPS::Real>>(mEMTPh3, "RXLoad", py::multiple_inheritance())
        .def(py::init<std::string, CPS::Logger::Level>(), "name"_a, "loglevel"_a = CPS::Logger::Level::off)
        .def("set_parameters", &CPS::EMT::Ph3::RXLoad::setParameters, "active_power"_a, "reactive_power"_a, "volt"_a)
		.def("connect", &CPS::EMT::Ph3::RXLoad::connect);

	py::class_<CPS::EMT::Ph3::Switch, std::shared_ptr<CPS::EMT::Ph3::Switch>, CPS::SimPowerComp<CPS::Real>>(mEMTPh3, "Switch", py::multiple_inheritance())
        .def(py::init<std::string, CPS::Logger::Level>(), "name"_a, "loglevel"_a = CPS::Logger::Level::off)
        .def("set_parameters", &CPS::EMT::Ph3::Switch::setParameters, "open_resistance"_a, "closed_resistance"_a, "closed"_a = false)
		.def("open", &CPS::EMT::Ph3::Switch::openSwitch)
		.def("close", &CPS::EMT::Ph3::Switch::closeSwitch)
		.def("connect", &CPS::EMT::Ph3::Switch::connect);


	py::class_<CPS::EMT::Ph3::SynchronGeneratorDQTrapez, std::shared_ptr<CPS::EMT::Ph3::SynchronGeneratorDQTrapez>, CPS::SimPowerComp<CPS::Real>>(mEMTPh3, "SynchronGeneratorDQTrapez", py::multiple_inheritance())
        .def(py::init<std::string, CPS::Logger::Level>(), "name"_a, "loglevel"_a = CPS::Logger::Level::off)
		.def("set_parameters_operational_per_unit", &CPS::EMT::Ph3::SynchronGeneratorDQTrapez::setParametersOperationalPerUnit,
			"nom_power"_a, "nom_volt"_a, "nom_freq"_a, "pole_number"_a, "nom_field_cur"_a, "Rs"_a, "Ld"_a, "Lq"_a, "Ld_t"_a, "Lq_t"_a, "Ld_s"_a,
			"Lq_s"_a, "Ll"_a, "Td0_t"_a, "Tq0_t"_a, "Td0_s"_a, "Tq0_s"_a, "inertia"_a, "init_active_power"_a, "init_reactive_power"_a,
			"init_terminal_volt"_a, "init_volt_angle"_a, "init_field_voltage"_a, "init_mech_power"_a);

}
