#pragma once
#include "Produs.h"
#include "Repo.h"
class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() = default;
};
class UndoAdd :public UndoAction {
	Produs p;
	GenRepo& repo;
public:
	UndoAdd(GenRepo& rep,const Produs& p):repo{rep},p{p} {}
	void doUndo() override {
		repo.remove(p);
	}
};
class UndoRemove :public UndoAction {
	Produs p;
	GenRepo& repo;
public:
	UndoRemove(GenRepo& repo,const Produs& p)noexcept :repo{repo},p{p}{}
	void doUndo() override {
		repo.add(p);
	}
};
class UndoModify :public UndoAction {
	Produs oel, el;
	GenRepo& repo;
public:
	UndoModify(GenRepo& repo, const Produs& oel,const Produs& el)noexcept :repo{repo},oel{oel},el{el}{}
	void doUndo() override {
		repo.modify(el, oel);
	}
};