#pragma once

#include <list>
#include <functional>
#include <algorithm>

namespace event
{
	template<typename T>
	using Delegate = std::function<void(const T&)>;

	template<typename T>
	class Subject;

	template<typename T>
	class Observer {
	private:
		Subject<T>* subject;
		Delegate<T> delegate;
	public:
		Observer() {}
		Observer(Subject<T>* event, Delegate<T> del) : subject(event), delegate(del) {
			subject->attach(this);
		}
		~Observer() {
			subject->detach(this);
		}

		void update(const T& event) {
			delegate(event);
		}
	};

	template<typename T>
	class Subject {
		template<typename T>
		using ObserverPair = std::pair<Observer<T>*, bool>;
	private:
		std::list<ObserverPair<T>> observers;
		T data;

	private:
		void notify() {
			for (ObserverPair<T>& observer : observers) {
				if (observer.second) {
					observer.first->update(data);
				}
			}
			observers.erase(
				std::remove_if(
					observers.begin(),
					observers.end(),
					[&](const ObserverPair<T>& obsp){
						return obsp.second == false;
					}),
				observers.end());
		}

	public:
		void attach(Observer<T>* observer) {
			observers.push_back({observer, true});
		}

		void detach(Observer<T>* observer) {
			auto&& res = *std::find_if(
				observers.begin(), 
				observers.end(), 
				[&](ObserverPair<T> obsp) {
					return obsp.first == observer;
				});
			res.second = false;
			//observers.remove(observer);
		}


		void update(const T& new_data) {
			data = new_data;
			notify();
		}

		Observer<T>* create_observer(Delegate<T> del) {
			return new Observer<T>(this, del);
		}
	};
}
