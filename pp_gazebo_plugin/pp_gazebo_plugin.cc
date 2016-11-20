/*
 * Copyright (C) 2014-2016 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#include <sstream>
#include <gazebo/msgs/msgs.hh>
#include "pp_gazebo_plugin.hh"

using namespace gazebo;

// Register this plugin with the simulator
GZ_REGISTER_GUI_PLUGIN(GUIExampleTimeWidget)

/////////////////////////////////////////////////
GUIExampleTimeWidget::GUIExampleTimeWidget()
  : GUIPlugin()
{
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
  // Set the frame background and foreground colors
  this->setStyleSheet(
      "QFrame { background-color : rgba(100, 100, 100, 255); color : white; }");

  // Create the main layout
  QHBoxLayout *mainLayout = new QHBoxLayout;

  // Create the frame to hold all the widgets
  QFrame *mainFrame = new QFrame();

  // Create the layout that sits inside the frame
  QHBoxLayout *frameLayout = new QHBoxLayout();

  // // QLabel *label = new QLabel(tr("Sim Time:"));

  // Create a time label
  // // QLabel *timeLabel = new QLabel(tr("00:00:00.00"));

  // Add the label to the frame's layout
  /* frameLayout->addWidget(label);
  frameLayout->addWidget(timeLabel);
  connect(this, SIGNAL(SetSimTime(QString)),
      timeLabel, SLOT(setText(QString)), Qt::QueuedConnection);
  */

  QPushButton *button1 = new QPushButton(tr("Konfiguracja eksperymentu"));
  QPushButton *button2 = new QPushButton(tr("Zarzadzanie robotami"));
  QPushButton *button3 = new QPushButton(tr("Wyniki"));

  frameLayout->addWidget(button1);
  frameLayout->addWidget(button2);
  frameLayout->addWidget(button3);

  connect(button1, SIGNAL(clicked()), this, SLOT(OnButton1()));
  connect(button2, SIGNAL(clicked()), this, SLOT(OnButton2()));
  connect(button3, SIGNAL(clicked()), this, SLOT(OnButton3()));

  // Add frameLayout to the frame
  mainFrame->setLayout(frameLayout);

  // Add the frame to the main layout
  mainLayout->addWidget(mainFrame);

  // Remove margins to reduce space
  frameLayout->setContentsMargins(8, 8, 8, 8);
  mainLayout->setContentsMargins(0, 0, 0, 0);

  this->setLayout(mainLayout);

  // Position and resize this widget
  this->move(0, 0);
  this->resize(800, 40);

  // Create a node for transportation
  // this->node = transport::NodePtr(new transport::Node());
  // this->node->Init("default");
  // this->statsSub = this->node->Subscribe("~/world_stats",
  //     &GUIExampleTimeWidget::OnStats, this);
}

/////////////////////////////////////////////////
GUIExampleTimeWidget::~GUIExampleTimeWidget()
{
}

void GUIExampleTimeWidget::OnButton1()
{
 QDialog *dialog1 = new QDialog();
 dialog1->setWindowTitle(tr("Konfiguracja eksperymentu")); 
 dialog1->show();
}

void GUIExampleTimeWidget::OnButton2()
{
 QDialog *dialog2 = new QDialog();
 dialog2->show();
}

void GUIExampleTimeWidget::OnButton3()
{
 QDialog *dialog3 = new QDialog();
 dialog3->show();
}

