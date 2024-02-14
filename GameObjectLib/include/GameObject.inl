#include "GameObject.h"

template<typename T>
T* GameObject::CreateComponent()
{
	T* component = new T();
	component->SetOwner(this);
	components.push_back(component);
	return component;
}

template<typename T>
T* GameObject::GetComponent() {
	for (Component* component : components) {
		T* typedComponent = dynamic_cast<T*>(component);
		if (typedComponent) {
			return typedComponent;
		}
	}
	return nullptr;
}