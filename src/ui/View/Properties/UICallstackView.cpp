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
#include "UICallstackView.h"
#include "ui_UICallstackView.h"
#include "Model/UIModel.h"
//******************************************************************************
enum emCallstackColumn {
	emCallstackColumnFrame,
	emCallstackColumnModule,
	emCallstackColumnFunction,
	emCallstackColumnAddres,
	emCallstackColumnPath,
	emCallstackColumnPDB,
	emCallstackColumnMax,
};
//******************************************************************************
UICallstackView::UICallstackView(QWidget* parent)
	: QFrame(parent)
	, ui(new Ui::UICallstackView)
{
	ui->setupUi(this);

	auto view = ui->callstack;

	UIInitTreeView(view);

	auto proxy_model = new UISortFilterProxyModel(this);
	proxy_model->setSourceModel(m_Model = new UITreeViewModel(view));
	proxy_model->SetCustomSort(emCallstackColumnAddres);
	view->setModel(proxy_model);

	m_Model->Insert(tr("Frame"), 50);
	m_Model->Insert(tr("Module"), 120);
	m_Model->Insert(tr("Function"), 200);
	m_Model->Insert(tr("Address"), 200);
	m_Model->Insert(tr("Path"), 400);
	m_Model->Insert(tr("PDB"), 400);

	Q_CONNECT(view, customContextMenuRequested, on_customContextMenuRequested);
}
//******************************************************************************
UICallstackView::~UICallstackView()
{
	for (auto& it : m_Symbols) {
		it->Close();
	}

	m_Symbols.clear();

	delete ui;
}
//******************************************************************************
void UICallstackView::OnUpdate(IMessage* msg)
{
	cxMSGProcess* process = msg->GetProcess();
	cxMSGDataCallstack callstack = msg->GetCallstack();

	for (ULONG index = 0; index < callstack.Count; index++) {
		auto symbol = std::make_shared<cxSymbolParser>(callstack.Data[index], process->m_ProcessId, msg->m_Time);

		m_Model->setRowCount(index + 1);
		m_Model->SetData(index, emCallstackColumnFrame, (int)index, Qt::AlignRight);
		m_Model->SetData(index, emCallstackColumnModule, symbol->m_ModuleName, Qt::AlignRight);
		m_Model->SetData(index, emCallstackColumnFunction, symbol->GetSymbol());
		m_Model->SetData(index, emCallstackColumnAddres, g_MSGFormat->FormatAddress(symbol->m_Address), Qt::AlignRight);
		m_Model->SetData(index, emCallstackColumnPath, symbol->m_ModulePath);
		m_Model->SetData(index, emCallstackColumnPDB, symbol->m_PDBPath);
		m_Model->SetIcon(index, emCallstackColumnFrame, GetVisionService()->GetCallstackIcon(symbol->IsKernelAddress()));

		m_Model->SetUserData(index, emCallstackColumnAddres, symbol->m_Address);

		symbol->OnBeginParse([this](cxSymbol* symbol) {
			ui->info->setText("loading: " + QStringFrom(symbol->m_ModulePath));
		});

		symbol->OnFinishParse([this, index](cxSymbol* symbol) {
			ui->info->setText("");
			m_Model->SetData(index, emCallstackColumnFunction, symbol->GetSymbol());
			m_Model->SetData(index, emCallstackColumnPDB, symbol->m_PDBPath);
			update();
		});

		m_Symbols.push_back(symbol);

		g_SymbolManager->Parse(symbol, g_MainLooper);
	}
}
//******************************************************************************
void UICallstackView::on_customContextMenuRequested(const QPoint& pos)
{
	auto index = ui->callstack->currentIndex();

	if (!index.isValid())
		return;

	QMenu menu;

	menu.addAction("Copy", [this, index]() {
		qApp->clipboard()->setText(m_Model->GetData(index.row(), index.column()).toString());
	});

	if (index.column() == emCallstackColumnPath || index.column() == emCallstackColumnPDB) {
		auto str = m_Model->GetData(index.row(), index.column()).toString();
		if (!str.isEmpty()) {
			menu.addSeparator();
			menu.addAction(g_res->icon_locate, "Locate", [str]() {
				g_PathLocate->LocateFile(QStringToCString(str));
			});
		}
	}

	menu.exec(QCursor::pos());
}
//******************************************************************************
