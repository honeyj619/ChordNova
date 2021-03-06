// SmartChordGen v3.0 [Build: 2020.11.27]
// (c) 2020 Wenge Chen, Ji-woon Sim.
// chorddata.cpp

#include <vector>
#include "chorddata.h"
#include "functions.h"

vector<int> rm_priority;

void ChordData::printInitial()
{
	fout << "(" << name << ")\n"
		  << "t = " << fixed << setprecision(1) << tension << ",  "
		  << "s = " << span << ",  ";
	fprint("vec = ", count_vec, "\0", ",  ", false);
	fprint("d = ", self_diff);
	fout << "n = " << s_size << ",  "
		  << "m = " << t_size << ",  "
		  << "n/m = " << noshowpoint << (double)s_size / t_size << ",  "
		  << "h = " << noshowpoint << thickness << ",  "
		  << "g = " << g_center << "%,  "
		  << "root: " << root_name << " (r = " << root << ")\n\n";
}

void ChordData::print(const ChordData& chord)
{
	fprint("-> ", chord.notes, " ", ", ");
	fout << "(" << chord.name << ")";
	switch(chord.overflow_state)
	{
		case Single:     fout << "*\n";   break;
		case Total:      fout << "**\n";  break;
		case NoOverflow: fout << "\n";    break;
	}
	fout << "k = " << fixed << setprecision(1) << chord.chroma << ",  "
		  << "c = " << chord.common_note << ",  "
		  << "ss = " << chord.sspan << ",  "
		  << "sv = " << chord.sv << ",  ";
	fprint("v = ", chord.vec);
	fout << "t = " << fixed << setprecision(1) << chord.tension << ",  "
		  << "s = " << chord.span << ",  ";
	fprint("vec = ", chord.count_vec, "\0", ",  ", false);
	fprint("d = ", chord.self_diff);
	fout << "n = " << chord.s_size << ",  "
		  << "m = " << chord.t_size << ",  "
		  << "n/m = " << noshowpoint << (double)chord.s_size / chord.t_size << ",  "
		  << "h = " << noshowpoint << chord.thickness << ",  "
		  << "g = " << chord.g_center << "%,  "
		  << "root: " << chord.root_name << " (r = " << chord.root << ")\n";
	fout << "Q = " << fixed << setprecision(1) << chord.Q_indicator << ",  "
		  << "x = " << chord.similarity << "%,  "
		  << "dr = " << chord.root - root << ",  "
		  << "dn = " << chord.s_size - s_size << ",  "
		  << "dt = " << fixed << setprecision(1) << chord.tension - tension << ",  "
		  << "ds = " << chord.span - span << ",  "
		  << "dg = " << chord.g_center - g_center << "%\n\n";
}

bool larger_t_size(const ChordData& data1, const ChordData& data2)
{ return data1.t_size >= data2.t_size; }

bool larger_s_size(const ChordData& data1, const ChordData& data2)
{ return data1.s_size >= data2.s_size; }

bool larger_tension(const ChordData& data1, const ChordData& data2)
{ return data1.tension >= data2.tension; }

bool larger_thickness(const ChordData& data1, const ChordData& data2)
{ return data1.thickness >= data2.thickness; }

bool larger_root(const ChordData& data1, const ChordData& data2)
{ return data1.root >= data2.root; }

bool larger_span(const ChordData& data1, const ChordData& data2)
{ return data1.span >= data2.span; }

bool larger_sspan(const ChordData& data1, const ChordData& data2)
{ return data1.sspan >= data2.sspan; }

bool larger_g_center(const ChordData& data1, const ChordData& data2)
{ return data1.g_center >= data2.g_center; }

bool larger_chroma(const ChordData& data1, const ChordData& data2)
{ return data1.chroma >= data2.chroma; }

bool larger_common(const ChordData& data1, const ChordData& data2)
{ return data1.common_note >= data2.common_note; }

bool larger_sv(const ChordData& data1, const ChordData& data2)
{ return data1.sv >= data2.sv; }

bool larger_similarity(const ChordData& data1, const ChordData& data2)
{ return data1.similarity >= data2.similarity; }

bool larger_Q_indicator(const ChordData& data1, const ChordData& data2)
{ return data1.Q_indicator >= data2.Q_indicator; }

bool superior_rm(const ChordData& data1, const ChordData& data2)
{ return rm_priority[data1.root_movement] <= rm_priority[data2.root_movement]; }


bool smaller_t_size(const ChordData& data1, const ChordData& data2)
{ return data1.t_size <= data2.t_size; }

bool smaller_s_size(const ChordData& data1, const ChordData& data2)
{ return data1.s_size <= data2.s_size; }

bool smaller_tension(const ChordData& data1, const ChordData& data2)
{ return data1.tension <= data2.tension; }

bool smaller_thickness(const ChordData& data1, const ChordData& data2)
{ return data1.thickness <= data2.thickness; }

bool smaller_root(const ChordData& data1, const ChordData& data2)
{ return data1.root <= data2.root; }

bool smaller_span(const ChordData& data1, const ChordData& data2)
{ return data1.span <= data2.span; }

bool smaller_sspan(const ChordData& data1, const ChordData& data2)
{ return data1.sspan <= data2.sspan; }

bool smaller_g_center(const ChordData& data1, const ChordData& data2)
{ return data1.g_center <= data2.g_center; }

bool smaller_chroma(const ChordData& data1, const ChordData& data2)
{ return data1.chroma <= data2.chroma; }

bool smaller_common(const ChordData& data1, const ChordData& data2)
{ return data1.common_note <= data2.common_note; }

bool smaller_sv(const ChordData& data1, const ChordData& data2)
{ return data1.sv <= data2.sv; }

bool smaller_similarity(const ChordData& data1, const ChordData& data2)
{ return data1.similarity <= data2.similarity; }

bool smaller_Q_indicator(const ChordData& data1, const ChordData& data2)
{ return data1.Q_indicator <= data2.Q_indicator; }

bool inferior_rm(const ChordData& data1, const ChordData& data2)
{ return rm_priority[data1.root_movement] >= rm_priority[data2.root_movement]; }


bool (*compare[_TOTAL][2]) (const ChordData&, const ChordData&) =
{ {larger_chroma, smaller_chroma}, {larger_tension, smaller_tension}, {larger_common, smaller_common},
  {larger_sv, smaller_sv},         {larger_t_size, smaller_t_size},   {larger_s_size, smaller_s_size},
  {larger_root, smaller_root},     {larger_span, smaller_span},       {larger_sspan, smaller_sspan},
  {larger_thickness, smaller_thickness},     {larger_g_center, smaller_g_center}, {larger_similarity, smaller_similarity},
  {larger_Q_indicator, smaller_Q_indicator}, {superior_rm, inferior_rm} };
