/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<ObjectFactory.cpp>
Purpose:<implement functions in ObjectFactory.h>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/16/2018>
-End Header --------------------------------------------------------*/
#include"GameObject.h"
#include"GameObjectManager.h"
#include"Component/Transform.h"
#include"ObjectFactory.h"
#include"json.h"
#include"Component/Body.h"
#include<unordered_map>
#include"ComponentMap.h"
#include"Component/UI.h"
//#include<string>
extern ComponentMap* gpComponentMap;
extern GameObjectManager* gpGameObjectManager;

ObjectFactory::ObjectFactory() {

}

bool SortRenderList( const GameObject* m1, const GameObject* m2) {
	return m1->renderLayer > m2->renderLayer;
}



void LoadScriptForGo(GameObject * go, Json::Value root) {

	for (size_t i = 0; i < root.size(); i++)
	{
		Script* p = go->AddScript(root[i].asString());
		if (p != nullptr)
		{
			p->Init();
		}
	}
	
}

GameObject* ObjectFactory::LoadGameObject(const char* filePath)
{
	GameObject* p = nullptr;
	FILE *fp;
	std::string  t = "../Resource/";
	t += filePath;
	t += ".txt";
	fopen_s(&fp, t.c_str(), "r");
	if (fp)
	{
		p = new GameObject();
		while (!feof(fp)) {
			char componentName[256] = { 0 };
			fscanf_s(fp, "%255s\n", componentName, 256 * sizeof(char));
			
			std::string stingComName = componentName;
			Component* pNemComponent = nullptr;
			
			if (pNemComponent != NULL)
			{
				pNemComponent->Serialize(&fp);
			}
		}
	}
	return p;

}

void ObjectFactory::LoadLevelFromTxt(const char* filePath) {
	FILE *fp;
	std::string  t = "../Resource/";
	t += filePath;
	t += ".txt";
	fopen_s(&fp, t.c_str(), "r");
	while (!feof(fp))
	{
		char objcetName[256] = { 0 };
		fscanf_s(fp, "%255s\n", objcetName, 256 * sizeof(char));
		std::string stingObjectName = objcetName;

		GameObject* pnewGameObject = LoadGameObject(stingObjectName.c_str());

		Transform* pT = dynamic_cast<Transform*>(pnewGameObject->GetComponent(TRANSFORM));
		if (pT)
		{
			pT->Serialize(&fp);
		}
	}
}


void ObjectFactory::LoadLevelFromJson(const char* filePath) {
	FILE *fp;
	std::string  t = "../Resource/GameScene/";
	t += filePath;
	t += ".json";
	fopen_s(&fp, t.c_str(), "r");
	if (!fp)
	{
		printf("read json fail");
		return;
	}
	std::string text = "";
	char buffer[256] = { 0 };
	while (!feof(fp))
	{
		
		fscanf_s(fp, "%255s\n", buffer, 256 * sizeof(char));
		text += buffer;
	}
	fclose(fp);

	Json::CharReaderBuilder builder;
	Json::CharReader* a = builder.newCharReader();
	//Json::Reader reader ;
	Json::Value root;
	std::string error;
	if (a->parse(text.c_str(), text.c_str() + text.size(), &root, &error))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
	{
		Json::Value::Members members = root.getMemberNames();

		for (size_t i = 0; i < members.size(); i++)
		{
			if (members[i] == "bullet") {
				int x = 0;
			}
			Json::Value gameObject = root[members[i]];
			LoadGameObject (members[i],gameObject);
		}
		gpGameObjectManager->GameObjectsRenderList.sort(SortRenderList);
	}
	else
	{
		printf("load json failed %s \n", t.c_str());
		printf("%s\n", error.c_str());
		system("pause");
	}

}

GameObject* ObjectFactory::LoadGameObject(std::string name, Json::Value newGameObject)
{
	Json::Value::Members members = newGameObject.getMemberNames();
	GameObject* p = nullptr;
	p = new GameObject(name);
	if (members.size()>0)
	{
		
		for (size_t i = 0; i < members.size(); i++)
		{
			
			if (members[i] == "render_order")
			{
				p->SetRenderOrder(newGameObject[members[i]].asInt());
				continue;
			}
			Json::Value component = newGameObject[members[i]];//a new component
			std::string stingComName = members[i];
			Component* pNemComponent = nullptr;
			pNemComponent = p->AddComponent(stingComName);
			if (pNemComponent != NULL)
			{
				pNemComponent->Serialize(component);
			}
		}	
	}
	Body* pBody = static_cast<Body*> (p->GetComponent(BODY));
	if (pBody != nullptr)
	{
		pBody->Init();
	}
	UserInterface* pUI = static_cast<UserInterface*> (p->GetComponent(UI));
	if (pUI != nullptr)
	{
		pUI->Init();
	}

	return p;

}

void ObjectFactory::LoadScript(const char* filePath) {
		
	FILE *fp;
	std::string  t = "../Resource/Script/";
	t += filePath;
	t += ".json";
	fopen_s(&fp, t.c_str(), "r");
	if (!fp)
	{
		printf("read json fail");
		return;
	}
	std::string text = "";
	char buffer[256] = { 0 };
	while (!feof(fp))
	{

		fscanf_s(fp, "%255s\n", buffer, 256 * sizeof(char));
		text += buffer;
	}
	fclose(fp);

	Json::CharReaderBuilder builder;
	Json::CharReader* a = builder.newCharReader();
	//Json::Reader reader ;
	Json::Value root;
	std::string error;
	if (a->parse(text.c_str(), text.c_str() + text.size(), &root, &error))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
	{
		Json::Value::Members members = root.getMemberNames();
		int c = gpGameObjectManager->GameObjects.size();
		for (size_t i = 0; i < members.size(); i++)
		{
			std::string name = members[i];
			
			for (int k = 0;k<c;++k)
			{
				if (gpGameObjectManager->GameObjects[k]->name == name)
				{
					 LoadScriptForGo(gpGameObjectManager->GameObjects[k],root[members[i]]);
				}
			}
			
		}
	}
	else
	{
		printf("load json failed %s \n", t.c_str());
		system("pause");
	}
}





