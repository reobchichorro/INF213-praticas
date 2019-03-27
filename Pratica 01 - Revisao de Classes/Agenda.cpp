#include <iostream>
#include <string>
#include "Agenda.h"

ItemAgenda::ItemAgenda() {

}
ItemAgenda::ItemAgenda(const std::string& desc, const Data & dt, const Horario & hr) {
    this->descricao = desc;
    this->setData(dt);
    this->setHorario(hr);
}
ItemAgenda::ItemAgenda(const ItemAgenda& it) {
    this->descricao = it.getDesc();
    this->setData(it.getData());
    this->setHorario(it.getHorario());
}

void ItemAgenda::setDesc(const std::string &desc) {
    this->descricao = desc;
}
void ItemAgenda::setData(const Data& dt) {
    this->d.setAno(dt.getAno());
    this->d.setMes(dt.getMes());
    this->d.setDia(dt.getDia());
}
void ItemAgenda::setHorario(const Horario& hr) {
    this->h.setHora(hr.getHora());
    this->h.setMinuto(hr.getMinuto());
    this->h.setSegundo(hr.getSegundo());
}

const std::string& ItemAgenda::getDesc() const {
    return this->descricao;
}
const Data& ItemAgenda::getData() const {
    return this->d;
}
const Horario& ItemAgenda::getHorario() const {
    return this->h;
}

Agenda::Agenda() {
    itens_existentes = 0;
}
void Agenda::inserirItem(const ItemAgenda& it) {
    itens[itens_existentes].setDesc(it.getDesc());
    itens[itens_existentes].setData(it.getData());
    itens[itens_existentes].setHorario(it.getHorario());
    itens_existentes++;
}
void Agenda::compromissosData(const Data& d) const{
    for(int i=0; i<itens_existentes; i++) {
        if(this->itens[i].getData().compData(d) == 0)
            std::cout << this->itens[i].getHorario() << " " << this->itens[i].getDesc() << std::endl;
    }
}
