// Project: Intelligent-Trashcan Simulator
// Engineering: Hakan Emre Kartal <hek@nula.com.tr>
// Creation Date: 15-06-2018
//
/*

   EN: This project; is a virtual game about the conflict between garbage generators 
   and garbage collectors. Garbage producers collect various weights and types of garbage 
   (household waste, medical waste, rotten fruit, rotten vegetables, plastic waste, paper 
   waste, chemical  waste and other types) they throw it in the  nearest garbage containers 
   at uncertain times. To garbage containers a load sensor that can detect its fullness is 
   installed. This load   periodically it is measured and  when it exceeds a certain amount, 
   the garbage collector is informed of its fullness with a signal (visual or auditory). 
   The garbage collector empties the closest full container to it. This is virtual game like 
   this continues.

   Keywords: Multi task, synch lock, oop modeling, virtual game.
   
   TR: Bu proje; çöp üreticiler ve çöp toplayýcýlar arasýndaki çekiþmeyi konu alan 
   sanal bir oyundur. Çöp üreticiler, ürettikleri çeþitli aðýrlýkta ve türlerde çöpleri 
   (evsel atýk, týbbi atýk, bozuk meyve, bozuk sebze, plastik atýk, kaðýt atýk, kimyasal  
   atýk ve diðer türlerde) kendilerine en yakýn çöp konteynerlerine belirsiz zamanlarda
   atarlar. Çöp konteynerlerine doluluðunu tespit edebilen yüksensörü takýlmýþtýr. Belirli
   periyotlarla bu yük ölçülür ve  belirli  bir  miktarý  aþtýðýnda  çöp  toplayýcýsýna  
   bir sinyal (görsel ya da iþitsel) ile doluluðu bildirilir. Çöp toplayýcýsý kendisine en 
   yakýn konumdaki dolu konteyneri boþaltýr. Bu sanal oyun bu þekilde devam eder.

   Anahtar kelimeler: Çoklu görev, senkronizasyon kilidi, nesne esaslý modelleme, 
                      sanal oyun.

*/

#include "stdafx.h"

/* 

   <Class Inheritance Diagram>

   Base
   |\
   | \_ Trashcan
   |     \
   |      \_ SmartTrashcan
   |\
   | \_ Garbage
   |     |\
   |     | \_ DomesticWaste
   |     |\
   |     | \_ MedicalWaste
   |     |\
   |     | \_ RottenFruit
   |     |\
   |     | \_ RottenVegetable
   |     |\
   |     | \_ PlasticWaste
   |     |\
   |     | \_ PaperWaste
   |     |\
   |     | \_ ChemicalWaste
   |     |\
   |     | \_ OtherWaste
   |     .
   |     .
   |     .
   |
   |\
   | \_ Synchronizer
   |     \
   |      \_ Lock
   |
   |_ Sensor
   |     \
   |      \_ LoadSensor
   |              \
   |               \_ TrashCanLoadSensor
    \
     \_ Controller
         \
          \_ PeriodicController
                  |\
                  | \_ TrashCanLoadController
                  |        \
                  |         \_ AlertedTrashCanLoadController
                   \
                    \_ Alert
                        |\
                        | \_ Exclamation
                         \
                          \_ Warning
*/

class CTrashcanLoadSensor : public CLoadSensor
{
private:
   
   CTrashcan *m_objSubject;
   
public:
   
   CTrashcanLoadSensor( CTrashcan *inTrashCan ) : m_objSubject(inTrashCan) 
   {}
   
   double Measure()
   {
      double l_fResult = 0.0;

      m_objSubject->Lock();
      __try 
      {
         for (int i = 0; i < m_objSubject->Count(); i++)
         { l_fResult += m_objSubject->Get( i )->Weight(); }
      }
      __finally
      { m_objSubject->Unlock(); }

      return (l_fResult / MaximumLoad());
   }

   double MaximumLoad() { return m_objSubject->Capacity(); }
   
};

typedef \
   enum TrashcanLoadStatus
   {
      TrashcanLoadStatusEmpty  = 0,
      TrashcanLoadStatusNormal = 1,
      TrashcanLoadStatusFull   = 2
   };

const \
   char *TrashcanLoadStatusStrings[] = \
   {
      "Empty",
      "Normal",
      "Full"
   };

class CTrashcanLoadController : public CPeriodicController
{

private:

   CTrashcan *m_objSubject;
   CTrashcanLoadSensor *m_objSensor;

   TrashcanLoadStatus m_enmStatus;

protected:

   virtual void DoStatusChanged()
   {
   /*
      switch (Status())
      {
         case TrashcanLoadStatus::TrashcanLoadStatusEmpty:
         { printf( "\n\n\rTRASH CAN (%s) EMPTY\n\n\r", Subject()->Identifier() ); }
         break;

         case TrashcanLoadStatus::TrashcanLoadStatusNormal:
         { printf( "\n\n\rTRASH CAN (%s) NORMAL\n\n\r", Subject()->Identifier() ); }
         break;

         case TrashcanLoadStatus::TrashcanLoadStatusFull:
         { printf( "\n\n\rTRASH CAN (%s) FULL\n\n\r", Subject()->Identifier() ); }
         break;
      }
   */
   }

public:

   CTrashcanLoadController( CTrashcan *inSubject ) : \
      CPeriodicController( 5000 ), \
      m_objSubject(inSubject), \
      m_objSensor(new CTrashcanLoadSensor( inSubject )), \
      m_enmStatus(TrashcanLoadStatus::TrashcanLoadStatusEmpty)
   {}

   ~CTrashcanLoadController( void )
   { delete m_objSensor; }

   void Run()
   {
      TrashcanLoadStatus l_enmStatus = m_enmStatus;

      switch (m_objSensor->Load())
      {
         case LoadClass::LoadClassUnknown:
         case LoadClass::LoadClassEmpty:
            l_enmStatus = TrashcanLoadStatus::TrashcanLoadStatusEmpty;
            break;
         case LoadClass::LoadClassBelowNormal:
         case LoadClass::LoadClassNormal:
         case LoadClass::LoadClassAboveNormal:
            l_enmStatus = TrashcanLoadStatus::TrashcanLoadStatusNormal;
            break;
         case LoadClass::LoadClassFull:
         case LoadClass::LoadClassOverload:
            l_enmStatus = TrashcanLoadStatus::TrashcanLoadStatusFull;
            break;
      }

      if (m_enmStatus != l_enmStatus)
      {
         m_enmStatus = l_enmStatus;
         DoStatusChanged();
      }
   }

   TrashcanLoadStatus Status() { return m_enmStatus; }
   CTrashcan *Subject() { return m_objSubject; }

};

class CAlertedTrashcanLoadController : public CTrashcanLoadController
{

private:

   CAlert *m_objAlert;

   void DestroyAlert()
   {
      CAlert *l_objAlert = m_objAlert;
      m_objAlert = NULL;

      if (l_objAlert != NULL)
      { delete l_objAlert; }
   }

protected:

   virtual void DoStatusChanged()
   {
      DestroyAlert();

      __super::DoStatusChanged();

      switch (Status())
      {
         case TrashcanLoadStatus::TrashcanLoadStatusFull:
         { m_objAlert = new CWarning(); }
         break;
      }
   }

public:

   CAlertedTrashcanLoadController( CTrashcan *inSubject ) : \
      CTrashcanLoadController( inSubject ),
      m_objAlert(NULL)
   {}

   ~CAlertedTrashcanLoadController( void )
   { DestroyAlert(); }

};

class CSmartTrashcan : public CTrashcan
{
private:

   CLock *m_objLock;
   CTrashcanLoadController *m_objController;

public:

   CSmartTrashcan( double inCapacity ) : \
      CTrashcan( inCapacity ),
      m_objLock(new CLock()),
      m_objController(new CAlertedTrashcanLoadController( this ))
   {}

   ~CSmartTrashcan( void )
   { 
      delete m_objController;
      delete m_objLock; 
   }

   TrashcanLoadStatus Status() 
   { return m_objController->Status(); }

};

class CSimulator : public CPeriodicController
{

private:

   CVector<CSmartTrashcan *> *m_objDistrict;

   class CSimulatorGarbageLoader : public CPeriodicController
   {
   private:

      CSimulator *m_objSimulator;

   public:

      CSimulatorGarbageLoader( CSimulator *inSimulator ) : \
         CPeriodicController( 1000 ),
         m_objSimulator(inSimulator)
      {}

      void Run()
      {
         int l_iIndex = (rand() % m_objSimulator->m_objDistrict->Count());
         CGarbage *l_objGarbage = GarbageGenerator( 0.01, 10.00 );
         CSmartTrashcan *l_objTrashCan = m_objSimulator->m_objDistrict->Get( l_iIndex );
      
         printf( "%.2f weighted garbage '%s' was created and thrown into the target trash '%s'.\n\r", 
                 l_objGarbage->Weight(), l_objGarbage->Identifier(), l_objTrashCan->Identifier() );

         l_objTrashCan->Drop( l_objGarbage );
      }

   };

   class CSimulatorGarbageCollector : public CPeriodicController
   {
   private:

      CSimulator *m_objSimulator;

   public:

      CSimulatorGarbageCollector( CSimulator *inSimulator ) : \
         CPeriodicController( 5000 ),
         m_objSimulator(inSimulator)
      {}

      void Run()
      {
         CSmartTrashcan *l_objTrashCan;

         for (int n = 0; n < m_objSimulator->m_objDistrict->Count(); n++)
         {
            l_objTrashCan = m_objSimulator->m_objDistrict->Get( n );

            if (l_objTrashCan->Status() == TrashcanLoadStatus::TrashcanLoadStatusFull)
            {
               l_objTrashCan->Empty();
               printf( "\n\n\rTRASH CAN (%s) COLLECTED\n\n\r", l_objTrashCan->Identifier() );
            }
         }
      }

   };

   CSimulatorGarbageLoader *m_objLoader;
   CSimulatorGarbageCollector *m_objCollector;

public:

   CSimulator( int inMaximumSmartTrashcan = 10, double inTrashcanCapacity = 200.0 ) : \
      CPeriodicController( 10000 ), \
      m_objDistrict(new CVector<CSmartTrashcan *>()),
      m_objLoader(new CSimulatorGarbageLoader( this )),
      m_objCollector(new CSimulatorGarbageCollector( this ))
   {
      for (int n = 0; n < inMaximumSmartTrashcan; n++)
      { m_objDistrict->Add( new CSmartTrashcan( inTrashcanCapacity ) ); }
   }

   ~CSimulator( void )
   { 
      delete m_objLoader;
      delete m_objCollector;
      delete m_objDistrict; 
   }

   void Run()
   {
      CSmartTrashcan *l_objTrashCan;

      ClrScr();

      GotoXY( 0, 0 );
      printf( "\n\n\r-----------------------------------------------------\n\n\r" );

      for (int n = 0; n < m_objDistrict->Count(); n++)
      {
         l_objTrashCan = m_objDistrict->Get( n );

         printf( "\t%s (%d) is %s\n\r", l_objTrashCan->Identifier(), 
                 l_objTrashCan->Count(), TrashcanLoadStatusStrings[ l_objTrashCan->Status() ] );
      }

      printf( "\n\r-----------------------------------------------------\n\r" );
   }

};

int _tmain( int inArgc, _TCHAR* inArgV[] )
{

   CSimulator *l_objSimulator = new CSimulator( 20, 200.0 );

   getchar();

   delete l_objSimulator;

	return 0;

}
