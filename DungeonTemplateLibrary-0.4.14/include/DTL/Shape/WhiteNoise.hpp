﻿/*#######################################################################################
	Copyright (c) 2017-2019 Kasugaccho
	Copyright (c) 2018-2019 As Project
	https://github.com/Kasugaccho/DungeonTemplateLibrary
	wanotaitei@gmail.com

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#######################################################################################*/
#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_SHAPE_WHITE_NOISE_HPP
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_SHAPE_WHITE_NOISE_HPP

/*#######################################################################################
	日本語リファレンス (Reference-JP)
	https://github.com/Kasugaccho/DungeonTemplateLibrary/wiki/dtl::shape::WhiteNoise-(形状クラス)/
#######################################################################################*/

#include <DTL/Base/Struct.hpp>
#include <DTL/Macros/constexpr.hpp>
#include <DTL/Macros/nodiscard.hpp>
#include <DTL/Random/RandomEngine.hpp>
#include <DTL/Type/Forward.hpp>
#include <DTL/Type/SizeT.hpp>
#include <DTL/Range/RectBaseWithValue.hpp>
#include <DTL/Utility/DrawJaggedRandom.hpp>

/*#######################################################################################
	[概要] "dtl名前空間"とは"DungeonTemplateLibrary"の全ての機能が含まれる名前空間である。
	[Summary] The "dtl" is a namespace that contains all the functions of "DungeonTemplateLibrary".
#######################################################################################*/
namespace dtl {
	inline namespace shape { //"dtl::shape"名前空間に属する

		//マスを指定した数値で埋める
		template<typename Matrix_Var_, typename Random_Engine_ = DTL_RANDOM_DEFAULT_RANDOM>
		class WhiteNoise : public ::dtl::range::RectBaseWithValue<WhiteNoise<Matrix_Var_>, Matrix_Var_>,
			public ::dtl::utility::DrawJaggedRandom<WhiteNoise<Matrix_Var_>, Matrix_Var_, Random_Engine_> {
		private:


			///// エイリアス (Alias) /////

			using Index_Size = ::dtl::type::size;
			using ShapeBase_t = ::dtl::range::RectBaseWithValue<WhiteNoise, Matrix_Var_>;
			using DrawBase_t = ::dtl::utility::DrawJaggedRandom<WhiteNoise, Matrix_Var_, Random_Engine_>;

			friend DrawBase_t;


			///// 基本処理 /////

			//STL
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				typename DTL_TYPE_ENABLE_IF<Matrix_::is_jagged::value, bool>::DTL_TYPE_EITYPE
				drawNormal(Matrix_&& matrix_, Random_Engine_&& random_engine_, Args_&& ... args_) const noexcept {
				const Index_Size end_y_{ this->calcEndY(matrix_.getY()) };
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					const Index_Size end_x_{ this->calcEndX(matrix_.getX(row)) };
					for (Index_Size col{ this->start_x }; col < end_x_; ++col)
						if (random_engine_.probability()) matrix_.set(col, row, this->draw_value, args_...);
				}
				return true;
			}

			//Normal
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				typename DTL_TYPE_ENABLE_IF<!Matrix_::is_jagged::value, bool>::DTL_TYPE_EITYPE
				drawNormal(Matrix_&& matrix_, Random_Engine_&& random_engine_, Args_&& ... args_) const noexcept {
				const Index_Size end_x_{ this->calcEndX(matrix_.getX()) };
				const Index_Size end_y_{ this->calcEndY(matrix_.getY()) };
				for (Index_Size row{ this->start_y }; row < end_y_; ++row)
					for (Index_Size col{ this->start_x }; col < end_x_; ++col)
						if (random_engine_.probability()) matrix_.set(col, row, this->draw_value, args_...);
				return true;
			}

		public:


			///// コンストラクタ (Constructor) /////

			using ShapeBase_t::ShapeBase_t;
		};

	}
}

#endif //Included Dungeon Template Library
