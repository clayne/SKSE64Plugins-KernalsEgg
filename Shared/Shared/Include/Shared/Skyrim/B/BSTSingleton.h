#pragma once

#include "Shared/PrecompiledHeader.h"



namespace Skyrim
{
	// BSTSingletonExplicit
	template <class T>
	struct BSTSingletonExplicit
	{
	public:
	};
	static_assert(std::is_empty_v<BSTSingletonExplicit<void>>);

	// BSTSingletonImplicit
	template <class T>
	struct BSTSingletonImplicit
	{
	public:
	};
	static_assert(std::is_empty_v<BSTSingletonImplicit<void>>);

	// BSTSingletonSDM
	template <class T>
	struct BSTSingletonSDMOpStaticBuffer
	{
	public:
	};
	static_assert(std::is_empty_v<BSTSingletonSDMOpStaticBuffer<void>>);

	template <class T, class Allocator = BSTSingletonSDMOpStaticBuffer<T>>
	struct BSTSDMTraits
	{
	public:
		using value_type     = T;
		using allocator_type = Allocator;
	};
	static_assert(std::is_empty_v<BSTSDMTraits<void>>);

	template <class Traits>
	struct BSTSingletonSDMBase :
		public Traits,                // 0
		public Traits::allocator_type // ?
	{
	public:
		using value_type     = typename Traits::value_type;
		using allocator_type = typename Traits::allocator_type;
	};
	static_assert(std::is_empty_v<BSTSingletonSDMBase<BSTSDMTraits<void>>>);

	template <class T, template <class> class Singleton = BSTSingletonSDMOpStaticBuffer>
	struct BSTSingletonSDM :
		public BSTSingletonSDMBase<BSTSDMTraits<T, Singleton<T>>> // 0
	{
	public:
	};
	static_assert(std::is_empty_v<BSTSingletonSDM<void>>);
}
