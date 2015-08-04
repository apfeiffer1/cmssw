#include "CondCore/Utilities/interface/PayloadInspectorModule.h"
#include "CondCore/Utilities/interface/JsonPrinter.h"
#include "CondFormats/Common/interface/BasicPayload.h"
#include "CondCore/CondDB/interface/Time.h"
#include "CondCore/CondDB/interface/PayloadReader.h"
#include <sstream>

namespace {

  class BasicPayloadPlot_data0 {
  public:
    BasicPayloadPlot_data0(){
    }

    std::string title() {
      return "Data0 vs run number";
    }

    std::string data( const boost::python::list& iovs ){
      cond::persistency::PayloadReader reader;
      // TO DO: add try /catch block                                                                                                                                                    
      reader.open();
      cond::utilities::JsonPrinter jprint("Run","data0");
      for( int i=0; i< len( iovs ); i++ ) {
	cond::Iov_t iov = boost::python::extract<cond::Iov_t>( iovs[i] );
	boost::shared_ptr<cond::BasicPayload> obj = reader.fetch<cond::BasicPayload>( iov.payloadId );
	jprint.append(boost::lexical_cast<std::string>(iov.since),boost::lexical_cast<std::string>(obj->m_data0 ));
      }
      return jprint.print();
    }
  };

  class BasicPayloadPlot_data1 {
  public:
    BasicPayloadPlot_data1(){
    }

    std::string title() {
      return "Data1 trend";
    }

    std::string data( const boost::python::list& iovs ){
      cond::persistency::PayloadReader reader;
      // TO DO: add try /catch block                                                                                                                                                 
                                                                                                                                                                                    
      reader.open();
      cond::utilities::JsonPrinter jprint("Run","data1");
      for( int i=0; i< len( iovs ); i++ ) {
	cond::Iov_t iov = boost::python::extract<cond::Iov_t>( iovs[i] );
	boost::shared_ptr<cond::BasicPayload> obj = reader.fetch<cond::BasicPayload>( iov.payloadId );
        jprint.append(boost::lexical_cast<std::string>(iov.since),boost::lexical_cast<std::string>(obj->m_data1 ));
      }
      return jprint.print();
    }
  };

}

PAYLOAD_INSPECTOR_MODULE( BasicPayload ){
  PAYLOAD_INSPECTOR_CLASS( BasicPayloadPlot_data0 );
  PAYLOAD_INSPECTOR_CLASS( BasicPayloadPlot_data1 );
}
