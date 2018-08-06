#pragma once
#include "SDK/SDK.hpp"

namespace Game {
	class Asset : public CBehavior
	{
	public:
		enum Size { Light, Standard, Heavy };

		// should be called once
		void init(Size size)
		{
			m_size = size;
		}
		Size getSize() const
		{
			return m_size;
		}

	protected:
		Size m_size;
	};
}