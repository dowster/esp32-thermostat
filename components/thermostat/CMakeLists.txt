# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(CMAKE_CXX_STANDARD 14)

set(COMPONENT_SRCS "Relay.cpp"
"Schedule.cpp"
"Temperature.cpp"
"TemperatureSensor.cpp"
"Thermostat.cpp")

set(COMPONENT_ADD_INCLUDEDIRS "include")

register_component()
