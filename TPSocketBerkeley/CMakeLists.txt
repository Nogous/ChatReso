cmake_minimum_required (VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)

project ("TPSocketBerkeley")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (TPSocketBerkeley "TPSocketBerkeley.cpp" "TPSocketBerkeley.h" "Connection.cpp" "Connection.h" "UDPConnection.cpp" "UDPConnection.h" "LibNetwork.h" "LibNetwork.cpp" "TCPConnection.cpp" "TCPConnection.h" "Terminal.cpp" "Terminal.h")

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
