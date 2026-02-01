// ##########################################################################
// #                                                                        #
// #                              CLOUDCOMPARE                              #
// #                                                                        #
// #  This program is free software; you can redistribute it and/or modify  #
// #  it under the terms of the GNU General Public License as published by  #
// #  the Free Software Foundation; version 2 or later of the License.      #
// #                                                                        #
// #  This program is distributed in the hope that it will be useful,       #
// #  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
// #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          #
// #  GNU General Public License for more details.                          #
// #                                                                        #
// #          COPYRIGHT: Antigravity AI                                     #
// #                                                                        #
// ##########################################################################

#ifndef CC_SF_ASSIGNMENT_DLG_HEADER
#define CC_SF_ASSIGNMENT_DLG_HEADER

// Local
#include <ccOverlayDialog.h>

// qCC_db
#include <ccHObject.h>

// GUI
#include <ui_sfAssignmentDlg.h>

class ccPointCloud;

//! Scalar field assignment dialog
class ccSFAssignmentDlg : public QDialog, public Ui::SFAssignmentDlg
{
	Q_OBJECT

public:
	//! Default constructor
	explicit ccSFAssignmentDlg(const ccHObject::Container& entities, QWidget* parent = nullptr);
	//! Destructor
	virtual ~ccSFAssignmentDlg() = default;

	//! Returns the assigned value
	ScalarType getAssignedValue() const;
	//! Returns the target SF name
	QString getSFName() const;

protected slots:
	//! Called when the target SF is changed
	void onSFChanged(int index);
	//! Called when the apply button is clicked
	void onApply();
	//! Called when a value is double clicked in the list
	void onValueDoubleClicked(QListWidgetItem* item);

signals:
	//! Signal emitted when the user wants to apply a value
	void applyValue(const QString& sfName, ScalarType value);

private:
	//! Refresh the list of values
	void refreshValues();

	//! Selected entities
	ccHObject::Container m_entities;
};

#endif // CC_SF_ASSIGNMENT_DLG_HEADER
