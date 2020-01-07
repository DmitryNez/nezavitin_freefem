/* Some freefem++ API */
#include <ff++.hpp>
#include "AFunction_ext.hpp"

using namespace Fem2D;
#include "AFunction.hpp"
#include "array_resize.hpp"

#include "json.hpp"
#include <iomanip>
#include <algorithm>
using namespace std;
#include <fstream>
using json = nlohmann::json;
json j;



class JsonFileT
{
    public:
    	json js;
    JsonFileT(){}
    
    void init(){
        js;
    }

    void destroy(){
    }

    ~JsonFileT(){}
};


bool ReadJson(JsonFileT* J, string* filename){
	ifstream input(*filename);
	input>>J->js;
	return true;
}

bool AddToJsonLong(JsonFileT* const & J,string* const & path,long* const & lng){
	J->js[*path]=*lng;
	return true;
}


bool AddToJsonDouble(JsonFileT* const & J,string* const & path,double* const & doub){
	J->js[*path]=*doub;
	return true;
}

bool AddToJsonString(JsonFileT* const & J,string* const & path, string* const & str){
	J->js[*path]=*str;
	return true;
}

bool AddToJsonLong1dArray( JsonFileT* const & J,string* const & path, KN<long>* const& array_long){
	for( int i = 0; i < array_long->n; i++){
		J->js[*path].push_back((*array_long)[i]);
	}
	return true;
}

bool AddToJsonDouble1dArray( JsonFileT* const & J,string* const & path, KN<double>* const& array_double){
	for( int i = 0; i < array_double->n; i++){
		J->js[*path].push_back((*array_double)[i]);
	}
	return true;
}

bool AddToJsonLong2dArray( JsonFileT* const & J,string* const & path, KNM <long>* const& array2d_long){
	for( int i = 0; i < array2d_long->M(); i++){
		for( int j = 0; j < array2d_long->N(); j++){
			J->js[*path][i].push_back((*array2d_long)(i,j));
		}

	} 
	return true;
}

bool AddToJsonDouble2dArray( JsonFileT* const & J,string* const & path, KNM <double>* const& array2d_double){
	for( int i = 0; i < array2d_double->M(); i++){
		for( int j = 0; j < array2d_double->N(); j++){
			J->js[*path][i].push_back((*array2d_double)(i,j));
		}
	}
	return true;
}

bool ExtractFromJSONLong(JsonFileT* const & J,string* const & path,long* const & lng){
	*lng =  J->js[*path];
	return true;
}

bool ExtractFromJSONDouble(JsonFileT* const & J,string* const & path,double* const & doub){
	*doub =  J->js[*path];
	return true;
}

bool ExtractFromJSONString(JsonFileT* const & J,string* const & path,string** const & str){
	**str =  J->js[*path];
	return true;
}

bool ExtractFromJSONDouble1dArray( JsonFileT* const & J,string* const & path, KN<double>* const& array_double){

	for (json::iterator it = J->js[*path].begin(); it != J->js[*path].end(); ++it) {
	    (*array_double)[it - J->js[*path].begin()] = *it;
	}

	return true;
}

bool ExtractFromJSONLong1dArray( JsonFileT* const & J,string* const & path, KN<long>* const& array_long){

	for (json::iterator it = J->js[*path].begin(); it != J->js[*path].end(); ++it) {
	    (*array_long)[it - J->js[*path].begin()] = *it;
	}

	return true;
}

bool ExtractFromJSONDouble2dArray( JsonFileT* const & J,string* const & path, KNM <double>* const& array2d_double){

	for (json::iterator it = J->js[*path].begin(); it != J->js[*path].end(); ++it) {

		for(json::iterator i = (*it).begin(); i!= (*it).end(); ++i){

			(*array2d_double)(it - J->js[*path].begin(),i-(*it).begin()) = (*it)[i-(*it).begin()];
		}
	    
	}
	return true;
}

bool ExtractFromJSONLong2dArray( JsonFileT* const & J,string* const & path, KNM <long>* const& array2d_long){
	
	for (json::iterator it = J->js[*path].begin(); it != J->js[*path].end(); ++it) {

		for(json::iterator i = (*it).begin(); i!= (*it).end(); ++i){

			(*array2d_long)(it - J->js[*path].begin(),i-(*it).begin()) = (*it)[i-(*it).begin()];
		}
	    
	}

	return true;
}

bool WriteJsonFile(JsonFileT* const& J,string* const& filename){

	ofstream output(*filename);
	output << setw(4) << J->js << endl;
    return true;

}


static void load_init(){

    Dcl_Type< JsonFileT* >(
        InitP< JsonFileT >,
        Destroy< JsonFileT >
    );

    zzzfff->Add(
        "JsonFile",
        atype<JsonFileT*>()
    );


Global.Add(
        "ReadJson", "(",
        new OneOperator2 < bool, JsonFileT* , string*> (ReadJson)
    );

    Global.Add(
        "WriteJsonFile", "(",
        new OneOperator2_ < bool,JsonFileT*,string* > (WriteJsonFile)
    );
    Global.Add(
        "AddToJsonLong", "(",
        new OneOperator3_ < bool,JsonFileT*,string*,long* > (AddToJsonLong)
    );
    Global.Add(
        "AddToJsonDouble", "(",
        new OneOperator3_ < bool,JsonFileT*,string*,double* > (AddToJsonDouble)
    );
    Global.Add(
        "AddToJsonString", "(",
        new OneOperator3_ < bool,JsonFileT*,string*,string* > (AddToJsonString)
    );
    Global.Add(
        "AddToJsonLong1dArray", "(",
        new OneOperator3_ < bool,JsonFileT*,string*, KN<long>* > (AddToJsonLong1dArray)
    );
    Global.Add(
        "AddToJsonDouble1dArray", "(",
        new OneOperator3_ < bool,JsonFileT*,string*, KN<double>* > (AddToJsonDouble1dArray)
    );
    Global.Add(
        "AddToJsonLong2dArray", "(",
        new OneOperator3_ < bool,JsonFileT*,string*, KNM<long>* > (AddToJsonLong2dArray)
    );
    Global.Add(
        "AddToJsonDouble2dArray", "(",
        new OneOperator3_ < bool,JsonFileT*,string*, KNM<double>* > (AddToJsonDouble2dArray)
    );
    Global.Add(
        "ExtractFromJSONLong", "(",
        new OneOperator3_ < bool,JsonFileT*,string*, long* > (ExtractFromJSONLong)
    );
    Global.Add(
        "ExtractFromJSONDouble", "(",
        new OneOperator3_ < bool,JsonFileT*,string*, double* > (ExtractFromJSONDouble)
    );
    Global.Add(
        "ExtractFromJSONString", "(",
        new OneOperator3_ < bool,JsonFileT*,string*, string** > (ExtractFromJSONString)
    );
    Global.Add(
        "ExtractFromJSONDouble2dArray", "(",
        new OneOperator3_ < bool,JsonFileT*,string*, KNM<double>* > (ExtractFromJSONDouble2dArray)
    );
    Global.Add(
        "ExtractFromJSONLong2dArray", "(",
        new OneOperator3_ < bool,JsonFileT*,string*, KNM<long>* > (ExtractFromJSONLong2dArray)
    );
   Global.Add(
        "ExtractFromJSONDouble1dArray", "(",
        new OneOperator3_ < bool,JsonFileT*,string*, KN<double>* > (ExtractFromJSONDouble1dArray)
    );
   Global.Add(
        "ExtractFromJSONLong1dArray", "(",
        new OneOperator3_ < bool,JsonFileT*,string*, KN<long>* > (ExtractFromJSONLong1dArray)
    );

}

/* Must have call to include into FF load engine */

LOADFUNC(load_init)