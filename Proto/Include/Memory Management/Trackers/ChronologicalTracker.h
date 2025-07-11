#pragma once
#include "Data Structures/List/ArrayList.h"
#include "ProtoString.h"


namespace Proto {

	namespace Memory {

		namespace Tracker {

			class ChronologicalTracker {
			public:
				static Array<String> all_transactions(void* instance_ptr);
				static void add_transaction(void* instance_ptr, String supplementary_information = String());
			protected:
			private:
				struct Record {
					void* instance_ptr;
					String supplementary_information;
				};
				static ArrayList<Record> records;
			};

		}

	}

}