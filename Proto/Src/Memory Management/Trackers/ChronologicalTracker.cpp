#include "Memory Management/Trackers/ChronologicalTracker.h"


namespace Proto {

	namespace Memory {

		namespace Tracker {

			ArrayList<ChronologicalTracker::Record> ChronologicalTracker::records = ArrayList<ChronologicalTracker::Record>();

			Array<String> ChronologicalTracker::all_transactions(void* instance_ptr) {
				size_t number_of_matching_records = 0;
				for (size_t i = 0; i < ChronologicalTracker::records.length(); ++i) {
					if (ChronologicalTracker::records.get(i).instance_ptr == instance_ptr) {
						++number_of_matching_records;
					}
				}
				Array<String> results(number_of_matching_records);
				size_t current_index = 0;
				for (size_t i = 0; i < ChronologicalTracker::records.length(); ++i) {
					if (ChronologicalTracker::records.get(i).instance_ptr == instance_ptr) {
						results[current_index++] = ChronologicalTracker::records.get(i).supplementary_information;
					}
				}
				return results;
			}

			void ChronologicalTracker::add_transaction(void* instance_ptr, String supplementary_information) {
				ChronologicalTracker::records.append(Record{ instance_ptr, supplementary_information });
				return;
			}

		}

	}

}