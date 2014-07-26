#pragma once


#define pmngr EntityManager::Instance()

//单例模式
class EntityManager
{
private:

	typedef map<int,BaseEntity*> EntityMap;

	EntityManager(void);
	~EntityManager(void);

	//static EntityManager* pEntityManager;

	//存储id和entity之间一一对应关系的数据结构,std::map?
	EntityMap entityMap;
	//map<int,BaseEntity*> entityMap;


	static int currentID;	//当前新注册ID号

public:
	static EntityManager* Instance();

	void RegisterEntity(BaseEntity * newEntity);

	BaseEntity* GetEntityFromID(int id)const;

	//从列表移除注册的Entity
	void RemoveEntity(BaseEntity * pEntity);
};

