#ifndef SDFInputDialog_H
#define SDFInputDialog_H

#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLineEdit>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>

#include <BALL/APPLICATIONS/QuEasyViz/SDFInputDataItem.h>

namespace BALL
{
	namespace VIEW
	{
		/** @class SDFInputDialog
		* @brief a dialog
		*
		* @todo
		*/
		class SDFInputDialog : public QDialog
		{
		
			Q_OBJECT
		public:
			/** @name Constructors and Destructors
			*/
			SDFInputDialog(SDFInputDataItem* item);
			SDFInputDialog();
			~SDFInputDialog();
		
			/** @name Accessors
			*/
		
			/** returns the activity numbers
			*/ 
			SortedList<int> numbers();
		
			bool centerDescriptorValues();
			bool centerResponseValues();
			bool inputOk();
		
		public slots:
			void getNumbers();
			void classNamesChange();

		private:
		
			/** @name Attributes
			*/
			QLineEdit* activity_edit_;
			QCheckBox* sd_descriptors_checkbox_;
			QCheckBox* center_descriptor_values_;
			QCheckBox* center_response_values_;
			QCheckBox* class_names_checkbox_;
			SortedList<int> numbers_;
			bool input_ok_;
			SDFInputDataItem* input_item_;
			vector<String>* property_names_;

		};
	}
}

 #endif