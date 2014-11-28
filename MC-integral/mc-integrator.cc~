// constructing vectors
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>


typedef std::vector<double> Data1D;


double f(double x) { return pow(x,4); }

class Segment
{
public:
  Data1D sample_;
  double start_;
  double end_;
  
  double mean_;
  double var_;
  
  Segment (double start, double end) {
    start_ = start;
    end_ = end;
    
    mean_ = 0;
    var_ = 0;
  }
};

class MCIntegrator
{
private:
  static bool SegmentOrder( Segment A, Segment B ) { return A.var_ < B.var_; }

public:
  std::vector<Segment> segments_;
  double mean_;
  double var_;
  
  MCIntegrator () {
    srand (time(NULL));
    
    mean_ = 0;
    var_ = 0;
  }

  void sink_last() {
    uint i = segments_.size() - 1;
    while ((i > 1)&&( segments_[i].var_ < segments_[i-1].var_ )) { std::swap(segments_[i], segments_[i-1]); i--; }
  }
  
  double randomReal(double a, double b) { return a + (b - a)*(double(rand()) / RAND_MAX); }

  // Finds mean of a sample data array
  double sampleMean (Data1D data) {
    double rez = 0;
    for (uint i = 0; i < data.size(); i++) { rez += data[i]; }
    return rez / data.size();
  }

  // Finds 1st order bias corrected standard deviation of the mean
  double sampleVar( Data1D data, double mean ) {
    double N = data.size();

    if (N > 2)
    {
      double rez = 0;

      for (uint i = 0; i < N; i++) { rez += pow(data[i] - mean, 2); }
  
      return rez / N / (N - 1);
    }
    return 0;
  }

  // Makes n measurements in selected segment segment
  void makeMeasurements(uint nMes, uint segIter) {
    for (uint j = 0; j < nMes; j++) 
    { 
      double x = randomReal(segments_[segIter].start_, segments_[segIter].end_);
      segments_[segIter].sample_.push_back( f(x) );
    }
  }
  
  // Generates a new segment at the end of the segments array, makes samples in it, then sinks it such that the array is sorted again
  void add_new_segment(double a, double b, int nMes) {
    segments_.push_back(Segment(a,b));
    int last = segments_.size() - 1;
    
    makeMeasurements(nMes, last);
    segments_[last].mean_ = (b - a)       * sampleMean(segments_[last].sample_);
    segments_[last].var_  = pow(b - a, 2) * sampleVar(segments_[last].sample_, segments_[last].mean_);
    
    sink_last();
  }

  // Deletes last segment, splits it into two, adds these new segments to the end, taking samples and sorting
  void split_last(int nMes) {
    uint last = segments_.size() - 1;
    double a = segments_[last].start_;
    double c = segments_[last].end_;
    double b = (a + c) / 2.0;
    
    segments_.erase(segments_.end());
    
    add_new_segment(a, b, nMes);
    add_new_segment(b, c, nMes);
  }
  

  
  double integrate(uint segNo, uint nMes) {
    double intervLength = 1.0 / segNo;
    
    
    // Initialize segments
    for (uint i = 0; i < segNo; i++) {
      add_new_segment(intervLength * i, intervLength * (i+1), nMes);
      
      mean_ += segments_[i].mean_;
      var_ += segments_[i].var_;
    }
    
    std::sort(segments_.begin(), segments_.end(), SegmentOrder);
  
    int iter = nMes * segNo;
    do {
      iter += 2 * nMes;
      
      mean_ -= segments_[segments_.size() - 1].mean_;    var_ -= segments_[segments_.size() - 1].var_;
      
      split_last(nMes);
      
      //makeMeasurements(1, last, nMes);
      
      mean_ += segments_[segments_.size() - 1].mean_;    var_ += segments_[segments_.size() - 1].var_;
      mean_ += segments_[segments_.size() - 2].mean_;    var_ += segments_[segments_.size() - 2].var_;
      
      //sink_last();
    
      std::cout << "iter: " << iter << ", segment no: " << segments_.size() << ", integral value: " << mean_ << ", expected error: " << sqrt(var_) << std::endl;
      for (uint i = 0; i < segments_.size(); i++) { std::cout << "(" << segments_[i].mean_ << ", " << segments_[i].start_ << ", " << segments_[i].end_ << ")" << std::endl; } std::cout << std::endl;
      
  } while ((iter < 100) && (100 * sqrt(var_) > mean_ ));
  std::cout << std::endl;
  
  return mean_;
}
  
  
};








int main ()
{
  MCIntegrator brr;
  brr.integrate(4, 5);
  
  
  return 0;
}
