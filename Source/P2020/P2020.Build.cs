// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class P2020 : ModuleRules
{
	public P2020(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivatePCHHeaderFile = "Public/P2020.h";

//		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
            "UMG",
			"Json", 
			"JsonUtilities" 
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		PrivateDependencyModuleNames.Add("OnlineSubsystem");

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			// Add UPL to add configrules.txt to our APK
			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", System.IO.Path.Combine(PluginPath, "StrategyGame_UPL.xml"));
		}
	}
}
