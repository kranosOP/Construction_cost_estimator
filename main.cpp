#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Structure to store material data
struct Material {
    string name;
    double pricePerUnit;
    int quantity;
};

// Structure to store labor data
struct Labor {
    string type;
    double costPerHour;
    int hoursRequired;
};

// Function to read materials from a file
vector<Material> loadMaterials(const string& filename) {
    vector<Material> materials;
    ifstream file(filename);
    string line;
    
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return materials;
    }
    
    while (getline(file, line)) {
        stringstream ss(line);
        Material mat;
        ss >> mat.name >> mat.pricePerUnit >> mat.quantity;
        materials.push_back(mat);
    }
    
    file.close();
    return materials;
}

// Function to read labor data from a file
vector<Labor> loadLabor(const string& filename) {
    vector<Labor> laborList;
    ifstream file(filename);
    string line;
    
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return laborList;
    }
    
    while (getline(file, line)) {
        stringstream ss(line);
        Labor labor;
        ss >> labor.type >> labor.costPerHour >> labor.hoursRequired;
        laborList.push_back(labor);
    }
    
    file.close();
    return laborList;
}

// Function to save cost summary to a file
void saveCostSummary(double materialCost, double laborCost) {
    ofstream file("cost_summary.txt");
    if (!file) {
        cerr << "Error creating file: cost_summary.txt" << endl;
        return;
    }
    file << "Total Material Cost: " << materialCost << endl;
    file << "Total Labor Cost: " << laborCost << endl;
    file << "Grand Total Cost: " << (materialCost + laborCost) << endl;
    file.close();
    cout << "Cost summary saved to cost_summary.txt" << endl;
}

// Function to read and display cost summary from the file
void displayCostSummary() {
    ifstream file("cost_summary.txt");
    if (!file) {
        cerr << "Error opening file: cost_summary.txt" << endl;
        return;
    }
    string line;
    cout << "\n--- Cost Summary ---" << endl;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// Function to calculate total material cost
double calculateMaterialCost(const vector<Material>& materials) {
    double totalCost = 0;
    for (const auto& mat : materials) {
        totalCost += mat.pricePerUnit * mat.quantity;
    }
    return totalCost;
}

// Function to calculate total labor cost
double calculateLaborCost(const vector<Labor>& laborList) {
    double totalCost = 0;
    for (const auto& labor : laborList) {
        totalCost += labor.costPerHour * labor.hoursRequired;
    }
    return totalCost;
}

// Function to update material data
void updateMaterial(vector<Material>& materials) {
    string name;
    cout << "Enter material name to update: ";
    cin >> name;
    for (auto& mat : materials) {
        if (mat.name == name) {
            cout << "Enter new price per unit: ";
            cin >> mat.pricePerUnit;
            cout << "Enter new quantity: ";
            cin >> mat.quantity;
            cout << "Material updated successfully!\n";
            return;
        }
    }
    cout << "Material not found!\n";
}

// Function to update labor data
void updateLabor(vector<Labor>& laborList) {
    string type;
    cout << "Enter labor type to update: ";
    cin >> type;
    for (auto& labor : laborList) {
        if (labor.type == type) {
            cout << "Enter new cost per hour: ";
            cin >> labor.costPerHour;
            cout << "Enter new hours required: ";
            cin >> labor.hoursRequired;
            cout << "Labor updated successfully!\n";
            return;
        }
    }
    cout << "Labor type not found!\n";
}

int main() {
    string materialFile = "materials.txt";
    string laborFile = "labor.txt";
    
    vector<Material> materials = loadMaterials(materialFile);
    vector<Labor> laborList = loadLabor(laborFile);
    
    double totalMaterialCost = calculateMaterialCost(materials);
    double totalLaborCost = calculateLaborCost(laborList);
    
    cout << "Total Material Cost: " << totalMaterialCost << endl;
    cout << "Total Labor Cost: " << totalLaborCost << endl;
    cout << "Grand Total Cost: " << (totalMaterialCost + totalLaborCost) << endl;
    
    saveCostSummary(totalMaterialCost, totalLaborCost);
    displayCostSummary();
    
    char choice;
    cout << "Do you want to update materials or labor costs? (m/l/n): ";
    cin >> choice;
    if (choice == 'm') {
        updateMaterial(materials);
    } else if (choice == 'l') {
        updateLabor(laborList);
    }
    
    return 0;
}
