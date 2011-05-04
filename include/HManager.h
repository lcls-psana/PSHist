#ifndef PSHIST_HMANAGER_H
#define PSHIST_HMANAGER_H

//--------------------------------------------------------------------------
// File and Version Information:
// 	$Id$
//
// Description:
//	Class HManager.
//
//------------------------------------------------------------------------

//-----------------
// C/C++ Headers --
//-----------------

#include <vector>
#include <string>

//----------------------
// Base Class Headers --
//----------------------

#include <iostream>

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

#include "PSHist/Tuple.h"
#include "PSHist/H1.h"
#include "PSHist/H2.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------


//		---------------------
// 		-- Class Interface --
//		---------------------

namespace PSHist {

/**
 *  This software was developed for the LCLS project.  If you use all or 
 *  part of it, please give an appropriate acknowledgment.
 *
 *
 *  HManager is an empty base class which holds information about ntuples/histograms. 
 *  The main reason is to be able to create and hold new histograms or/and ntuples
 *  without knowing without knowing what the underlying system is. For example,
 *  it might be root, hbook, hyppo etc.
 *  
 *  Usage
 *  =====
 *  #include "PSHist/HManager.h"
 *  #include "RootHist/RootHManager.h"
 *  #include "PSHist/H1.h"
 *  #include "PSHist/H2.h"
 *  #include "PSHist/Tuple.h"
 *  
 *  
 *  
 *  1. Create a HManager with specific constructor (root for example):
 *
 *            PSHist::HManager *hMan = new RootHist::RootHManager("my-output-file.root", "RECREATE");
 *
 *  2. Create histograms
 *
 *            PSHist::H1 *pHis1f = hMan->hist1f("His1 float  title",100,0.,1.);
 *            PSHist::H2 *pHis2d = hMan->hist2d("His2 double title",100,0.,1.,100,0.,1.);
 *
 *     Create ntuples
 *
 *            PSHist::Tuple *nt = hMan->ntuple("EXP Data");
 *
 *     and define the ntuple parameters by names:
 *
 *                                            nt->parameter("beamEnergy");
 *                                            nt->parameter("beamCurrent");
 *     or by pointers:
 *
 *            PSHist::TupleParameter *p_beamEnergy  = nt->parameter("beamEnergy");
 *            PSHist::TupleParameter *p_beamCurrent = nt->parameter("beamCurrent");
 *
 *  3. Fill histograms
 *
 *            pHis1f -> fill(x,[weight]);        // once per event
 *            pHis2d -> fill(x,y,[weight]);
 *
 *     Fill ntuple by name:
 *  
 *            nt     -> fill("beamEnergy",  E);  // once per event
 *            nt     -> fill("beamCurrent", I);
 *
 *     or by pointers:
 *            p_beamEnergy  -> fill(E);          // once per event
 *            p_beamCurrent -> fill(I);
 *
 *            nt   -> addRow();                  // once per event
 *
 *  4. Write the data into a file:
 *
 *            hMan -> write();                   // at the end of job
 *            delete hMan;
 *
 *  @see AdditionalClass
 *
 *  @version $Id$
 *
 *  @author Mikhail S. Dubrovin
 */


class HManager  {
public:

  // Default constructor
  HManager (){
    std::cout << "HManager::HManager () - empty, abstract class object constructor." << std::endl;
  }

  // Destructor
  virtual ~HManager (){
    std::cout << "HManager::~HManager () - empty abstract class object distructor." << std::endl;
  }

private:

  // Data members
  
  //std::string m_nt_name;

  // Copy constructor and assignment are disabled by default
  HManager ( const HManager& ) ;
  HManager& operator = ( const HManager& ) ;

//------------------
// Static Members --
//------------------

public:

  enum { type_int, 
         type_float, 
         type_double };

    virtual H1 *hist1d(const std::string &name, const std::string &title, int nbins, double xlow, double xhigh) = 0;

   /*
   virtual H1 *hist1f(const std::string &hTitle, int nBins, double low, double high) = 0;

   virtual H1 *hist1d(const std::string &hTitle, int nBins, double low, double high) = 0;

   virtual H2 *hist2i(const std::string &hTitle, int XnBins, double Xlow, double Xhigh, 
                                                int YnBins, double Ylow, double Yhigh) = 0;

   virtual H2 *hist2f(const std::string &hTitle, int XnBins, double Xlow, double Xhigh, 
                                                int YnBins, double Ylow, double Yhigh) = 0;

   virtual H2 *hist2d(const std::string &hTitle, int XnBins, double Xlow, double Xhigh, 
                                                int YnBins, double Ylow, double Yhigh) = 0;

   virtual Tuple *tuple(const std::string &tTitle) = 0;
   */

   // This function returns a pointer to the ntuple with the given title. 
   // If the ntuple is known (ie. there is an ntuple with that title), the
   // existing ntuple is returned. If it is not known, a new one is created. 

   virtual int write() = 0;

   // write the ntuples/histograms into the file. 
   // Return 0 if successful,
   // non-0 otherwise.
   
   // Selectors (const)

   // Modifiers
};

} // namespace PSHist

#endif // PSHIST_HMANAGER_H
