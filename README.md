Paleidimas:
1. Paleidžiamas Visual Studio Code administratoriaus teisėmis
2. Pajungiamas terminalas ir suvedamos šios komandinės eilutes: 
rm -rf build
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
3. Testai paleidžiami komandine eilute ./CalculatorTests
4. Skaičiuotuvas paleidžiamas komandine eilute ./Calculator
