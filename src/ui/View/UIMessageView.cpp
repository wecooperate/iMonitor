//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#include "stdafx.h"
#include "UIMessageView.h"
//******************************************************************************
UIMessageView::UIMessageView(QWidget* parent)
	: QTreeView(parent)
{
	setObjectName(QString::fromUtf8("UIMessageView"));
	setContextMenuPolicy(Qt::CustomContextMenu);
	setFrameShape(QFrame::StyledPanel);
	setLineWidth(0);
	setFocus();

	UIInitTreeView(this);
	setSortingEnabled(false);

	header()->setStretchLastSection(false);
	viewport()->installEventFilter(new UIEventFilter(this));

	setModel(new UIMSGModel(this));

	Q_CONNECT(this, customContextMenuRequested, on_customContextMenuRequested);
	Q_CONNECT(this, doubleClicked, on_doubleClicked);
	Q_CONNECT(selectionModel(), currentChanged, on_currentChanged);

	HandleEvent(emServiceEventRuleBeginApply, [this]() {
		ShowProgressDialog();
	});

	HandleEvent(emServiceEventRuleFinishApply, [this]() {
		HideProgressDialog();
	});

	for (int i = 0; i < GetMessageService()->GetColumnCount(); i++) {
		setColumnWidth(i, GetMessageService()->GetColumn(i)->GetWidth());
	}
}
//******************************************************************************
UIMessageView::~UIMessageView()
{
	HideProgressDialog();
}
//******************************************************************************
void UIMessageView::ShowProgressDialog(void)
{
	HideProgressDialog();

	auto main_view = g_UIManager->GetView(SCHEME_MAIN_VIEW);
	m_Progress = new QProgressDialog(main_view);
	m_Progress->setWindowTitle(main_view->windowTitle());
	m_Progress->setMaximum(GetMessageService()->GetTotalCount());
	m_Progress->setCancelButton(nullptr);
	m_Progress->setWindowFlags(m_Progress->windowFlags() & ~(Qt::WindowCloseButtonHint | Qt::WindowContextHelpButtonHint));
	m_Progress->setWindowModality(Qt::ApplicationModal);
	m_Progress->setMinimumDuration(10);
	m_Progress->setValue(23);
	m_Progress->setStyleSheet("background-color:#fefefe; chunk: {border: 1px solid gray; }");
	m_Progress->setMinimumWidth(400);
	m_Progress->show();

	m_ProgressTimer = new QTimer(this);

	connect(m_ProgressTimer, &QTimer::timeout, [this]() {
		auto count = GetMessageService()->GetRuleApplyIndex();
		if (!m_Progress)
			return;
		m_Progress->setValue(count);
		if (!m_Progress)
			return;
		m_Progress->setLabelText(QString("Processing %1 of %2").arg(count).arg(m_Progress->maximum()));
	});

	m_ProgressTimer->start(10);
}
//******************************************************************************
void UIMessageView::HideProgressDialog(void)
{
	if (!m_Progress)
		return;

	m_ProgressTimer->stop();
	m_Progress->close();

	delete m_Progress;
	delete m_ProgressTimer;

	m_Progress = nullptr;
	m_ProgressTimer = nullptr;
}
//******************************************************************************
void UIMessageView::on_customContextMenuRequested(const QPoint& pos)
{
	auto index = currentIndex();

	QMenu menu;

	if (!GetMenuService()->InitContextMenu(index.row(), index.column(), &menu))
		return;

	menu.exec(QCursor::pos());
}
//******************************************************************************
void UIMessageView::on_doubleClicked(const QModelIndex& index)
{
	UIMSGIndex msg(index);

	if (!msg)
		return;

	auto view = g_UIManager->GetView(SCHEME_PROPERTIES_VIEW);
	view->setParent(this, Qt::Window);
	view->setProperty("msg", QVariant::fromValue((void*)(IMessage*)msg));
	view->show();
}
//******************************************************************************
void UIMessageView::on_currentChanged(const QModelIndex& current, const QModelIndex& previous)
{
}
//******************************************************************************
