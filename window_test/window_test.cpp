﻿#include "stdafx.h"
#include "Form1.h"
#include "props.h"
#include "settings.h"

Settings settings;

using namespace window_test;

static public ref class PTR : public System::Windows::Forms::Form
{
public:
	static Form1 ^ window;
	static TLVar ^ array;
};


System::Void props::button1_Click(System::Object^  sender, System::EventArgs^  e) {
	int size = 8, level = 2;
	if (radioButton1->Checked)
		size = 4;
	else if (radioButton2->Checked)
		size = 6;
	if (radioButton7->Checked)
		level = -1;
	else if (radioButton4->Checked)
		level = 0;
	else if (radioButton5->Checked)
		level = 1;
	settings.level = level;
	settings.size = size;
	this->Visible = false;

}

System::Void props::props_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
	if (!Visible) {
		PTR::array = gcnew TLVar();
		PTR::window->panel1->Controls->Clear();
		TVar ^var;
		var = (PTR::array->FindVar(0, PTR::array->GetFirst()));
		if (var) do
		{
			PTR::window->panel1->Controls->Add(var->n);
			var = var->next;
		} while (var);
		PTR::window->label1->Visible = true;
		PTR::window->label4->Visible = true;
		PTR::window->label1->Text = (System::Convert::ToString(PTR::array->b_score));
		PTR::window->label4->Text = (System::Convert::ToString(PTR::array->r_score));
		PTR::window->label2->Visible = true;
	}
}

System::Void Form1::sett_Click(System::Object^  sender, System::EventArgs^  e) {
	props ^ n_g = gcnew props();
	n_g->Visible = true;
}



System::Void cell::cell_Click(System::Object^  sender, System::EventArgs^  e) {
	// human turn
	TVar ^var;
	int test = (int)(((Control^)sender)->Tag);
	var = (PTR::array->FindVar((int)(((Control^)sender)->Tag), PTR::array->GetFirst()));
	if (var->n->inc('b')) 
		PTR::array->explosion(settings.size, (int)(((Control^)sender)->Tag), 'b');
	
	// refresh the score
	PTR::array->b_score = PTR::array->GetScore('b');
	PTR::window->label1->Text = (System::Convert::ToString(PTR::array->b_score));
	// prepare AI turn
	PTR::window->label2->Visible = false;
	PTR::window->label7->Visible = true;
	//bool testt = PTR::window->label3->Visible; // И ДАЖЕ ТЕСТТ ПРИСВАИВАЕТСЯ ТРУ!!!!!!!111111
	//PTR::window->label3->Visible = true;
	PTR::window->panel1->Enabled = false;
	_sleep(1000);
	PTR::window->panel1->Enabled = true;
	// AI turn	 
	PTR::array->ai(settings.size, settings.level);
	// refresh the score
	PTR::array->r_score = PTR::array->GetScore('r');
	PTR::window->label4->Text = (System::Convert::ToString(PTR::array->r_score));
	// prepare human turn
	PTR::window->label2->Visible = true;
	PTR::window->label7->Visible = false;
	// redraw

		var = (PTR::array->FindVar(0, PTR::array->GetFirst()));
		if (var) do
		{
			var->n->display();
			var = var->next;
		} while (var);

	// check if the game is over
	if ((PTR::array->b_score >= PTR::array->w_score) && (PTR::array->b_score>PTR::array->r_score))
		PTR::array->who_won = 'b';
	if ((PTR::array->r_score >= PTR::array->w_score) && (PTR::array->r_score>PTR::array->b_score))
		PTR::array->who_won = 'r';
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Âêëþ÷åíèå âèçóàëüíûõ ýôôåêòîâ Windows XP äî ñîçäàíèÿ êàêèõ-ëèáî ýëåìåíòîâ óïðàâëåíèÿ
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Ñîçäàíèå ãëàâíîãî îêíà è åãî çàïóñê
	PTR::window = gcnew Form1();
	Application::Run(PTR::window);
	return 0;
}
