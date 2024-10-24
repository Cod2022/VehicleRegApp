#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Fields {
    std::string type;
    std::string model;
    std::string brand;
    int year;
    int weight;
};

class Vehicle {
protected:
    inline static int counter = 0;
    int id;
    Fields fields;

public:
    Vehicle(): id(++counter) {}

    Vehicle(const Fields& _fields): fields(_fields), id(++counter) {}

    virtual const std::string toString() const {
        const std::string _fields = "id:" + std::to_string(id) + "\n"\
                                    "type:" + fields.type + "\n"\
                                    "brand:" + fields.brand + "\n"\
                                    "model:" + fields.model + "\n"\
                                    "year:" + std::to_string(fields.year) + "\n"\
                                    "weight:" + std::to_string(fields.weight);
        return _fields;
    }

    virtual void print(std::ostream& out) const {
        out << "id:" << id
        << "\ntype:" << fields.type 
        << "\nbrand:" << fields.brand
        << "\nmodel:" << fields.model
        << "\nyear:" << fields.year
        << "\nweight:" << fields.weight;
    }

    virtual void createFields(std::istream& in) {
        std::string _type;
        std::string _brand;
        std::string _model;
        int _year;
        int _weight;
        in >> _type >> _brand >> _model >> _year >> _weight;
        setFields(_type, _brand, _model, _year, _weight);    
    }

    const int getId() const { return id; }

    const Fields& getFields() const { return fields; }

    Fields& setFields(const std::string& _type, const std::string& _brand, const std::string& _model, int _year, int _weight) {
        fields.type = _type;
        fields.brand = _brand;
        fields.model = _model;
        fields.year = _year;
        fields.weight = _weight;
        return fields;
    }
};

class Car: public Vehicle {
private:
    int owners;

public:
    Car(): Vehicle() {}

    Car(const Fields& _fields, int _owners): Vehicle(_fields), owners(_owners) {}

    const std::string toString() const override  {
        std::string _fields = Vehicle::toString() + "\nowners:" + std::to_string(owners);
        return _fields;                     
    }

    void print(std::ostream& out) const override {
        Vehicle::print(out);
        out << "\nowners:" << owners;  
    }

    void createFields(std::istream& in) override {
        int _owners;
        Vehicle::createFields(in);
        in >> _owners;
        setOwners(_owners);
    }

    int setOwners(int _owners) {
        owners = _owners;
        return owners;
    }
  
};

std::ostream& operator << (std::ostream& out, const Vehicle& vehicle) {
    vehicle.print(out);
    return out;
}

std::istream& operator >> (std::istream& in, Vehicle& vehicle) {
    vehicle.createFields(in);
    return in;
}

class Controller {
private:
    std::vector<Vehicle*> vehicles;

public:

    void showAll() {
        if (!vehicles.empty()) {
            for (const auto& vehicle : vehicles) {
                std::cout << *vehicle << "\n" << "\n";
            }
        } else {
            std::cout << "Вы пока не добавили ни одной записи!";
        }   
    }

    void addVehicle(Vehicle& vehicle) {
        vehicles.emplace_back(&vehicle); 
    }

    void writeToFile(const std::string& filename) {
        std::ofstream out;
        out.open(filename, std::ios_base::app);
        if (out.is_open() && !(vehicles.empty())) {
            for (const auto& vehicle : vehicles) {
                out << *vehicle << "\n" << "\n";
            }
        }
        out.close();
    }

    const std::vector<Vehicle*>& getVehicles() { return vehicles; }
  
};

