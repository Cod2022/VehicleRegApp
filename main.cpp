#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "vehicle.cpp"

int main() {
    Controller cont;
    Car c({"M", "B", "T", 123, 432}, 3);
    Vehicle v({"v", "B", "T", 1, 4});
    cont.addVehicle(c);
    cont.addVehicle(v);
    cont.showAll();
    cont.writeToFile("vehicles.txt");

}