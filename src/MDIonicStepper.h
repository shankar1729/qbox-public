////////////////////////////////////////////////////////////////////////////////
//
// MDIonicStepper.h:
//
////////////////////////////////////////////////////////////////////////////////
// $Id: MDIonicStepper.h,v 1.3 2003-12-02 20:25:28 fgygi Exp $

#ifndef MDIONICSTEPPER_H
#define MDIONICSTEPPER_H

#include "IonicStepper.h"

class MDIonicStepper : public IonicStepper
{
  private:
  
  vector<vector<double> > taum_;
  double th_temp_;
  double th_time_;
  double eta_;
  bool thermostat_;
  void stoermer_start(const vector<vector<double> >& fion);
  void stoermer_end(const vector<vector<double> >& fion);

  public:
  
  MDIonicStepper(Sample& s) : IonicStepper(s)
  {
    thermostat_ = ( s.ctrl.thermostat == "ON" );
    th_temp_ = s.ctrl.th_temp;
    th_time_ = s.ctrl.th_time;
    eta_ = 0.0;
    taum_.resize(tau0_.size());
    for ( int is = 0; is < taum_.size(); is++ )
      taum_[is].resize(tau0_[is].size());
  }

  void update(const vector<vector< double> >& fion);
  void preprocess(const vector<vector<double> >& fion) { stoermer_start(fion);}
  void postprocess(const vector<vector<double> >& fion) { stoermer_end(fion);}
  double eta(void) const { return eta_; }
};

#endif
