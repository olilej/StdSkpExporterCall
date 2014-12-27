// SkpExporter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include "slapi\import_export\modelexporterplugin.h"

typedef SketchUpModelExporterInterface* (*GetExporterPtr)(void);

int _tmain(int argc, char* argv[])
{
	if (argc == 0)
		return 0;

	HINSTANCE Handle = LoadLibrary(".\\Exporters\\skp2dae.dll");
 
	if (!Handle)
		return -1;

	GetExporterPtr ExporterPtr = (GetExporterPtr)GetProcAddress(Handle,"GetSketchUpModelExporterInterface");
	SketchUpModelExporterInterface* Exporter = ExporterPtr();

	if (Exporter->GetFileExtensionCount() > 0)
	{
		for (int i = 1; i < argc; i++)
		{
			const std::string input_skp(argv[i]);
			const std::string output = input_skp + "." + Exporter->GetFileExtension(0);
			Exporter->ConvertFromSkp(input_skp, output, NULL, NULL);
		}
	}
	FreeLibrary(Handle);
	return 0;
}
