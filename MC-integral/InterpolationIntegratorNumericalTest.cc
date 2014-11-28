#include "InterpolationIntegratorNumerical.hh"


double f1(double x, double y) { return 1; }
double f2(double x, double y) { return 1 + x; }
double f3(double x, double y) { return 1 + x * x + y * y; }
double f4(double x, double y) { return x * y * y; }

double g1(double x) { return 1; }
double g2(double x) { return x; }
double g3(double x) { return pow(x, 3) - 3*x + 3; }



int main ()
{  
  InterpIntegratorEdge funIntegrator1;
  double rez1D_1 = funIntegrator1.integrate(g1, 1.0e-5); 
  double rez1D_2 = funIntegrator1.integrate(g2, 1.0e-5); 
  double rez1D_3 = funIntegrator1.integrate(g3, 1.0e-5); 
  
  InterpIntegratorTriangle funIntegrator2;
  double rez2D_1 = funIntegrator2.integrate(f1, 1.0e-5);
  double rez2D_2 = funIntegrator2.integrate(f2, 1.0e-5);
  double rez2D_3 = funIntegrator2.integrate(f3, 1.0e-5);
  double rez2D_4 = funIntegrator2.integrate(f4, 1.0e-5);
  
  std::cout << "---------------------------Summary: -----------------------------------------" << std::endl;
  std::cout << "Integrating f(x) = 1            over unit edge. Expected: 1.00000, result: " << rez1D_1 << std::endl;
  std::cout << "Integrating f(x) = x            over unit edge. Expected: 1.41421, result: " << rez1D_2 << std::endl;
  std::cout << "Integrating f(x) = x^3 - 3x + 3 over unit edge. Expected: 2.29601, result: " << rez1D_3 << std::endl;
  std::cout << "-----------------------------------------------------------------------------" << std::endl;
  std::cout << "Integrating f(x,y) = 1             over unit edge. Expected: 0.500000, result: " << rez2D_1 << std::endl;
  std::cout << "Integrating f(x,y) = 1 + x         over unit edge. Expected: 0.707107, result: " << rez2D_2 << std::endl;
  std::cout << "Integrating f(x,y) = 1 + x^2 + y^2 over unit edge. Expected: 0.751156, result: " << rez2D_3 << std::endl;
  std::cout << "Integrating f(x,y) = x * y^2       over unit edge. Expected: 0.526026, result: " << rez2D_4 << std::endl;
  
  return 0;
}

