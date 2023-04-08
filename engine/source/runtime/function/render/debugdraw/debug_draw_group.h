#pragma once

#include <mutex>
#include <string>
#include <list>
#include "debug_draw_primitive.h"
#include "debug_draw_font.h"


namespace SimpleEngine {
	/// <summary>
	/// 基础图形的组，可以管理里面的基础图形
	/// </summary>
	class DebugDrawGroup
	{
	public:
		~DebugDrawGroup() { clear(); }//清理组内所有物体
		void clear();

		void mergeFrom(DebugDrawGroup* group);//合并两个组的内容

		//组名
		void setName(const std::string& name) { m_name = name; }
		const std::string& getName() const { return m_name; }

		//获取组内图形数量
		size_t getPointCount(bool no_depth_test) const;
		size_t getLineCount(bool no_depth_test) const;
		size_t getTriangleCount(bool no_depth_test) const;
		size_t getUniformDynamicDataCount() const;
		size_t getSphereCount(bool no_depth_test) const;
		size_t getCylinderCount(bool no_depth_test) const;
		size_t getCapsuleCount(bool no_depth_test) const;
		size_t getTextCharacterCount() const;

		//写顶点数据到vertexs
		void writePointData(std::vector<DebugDrawVertex>& vertexs, bool no_depth_test);
		void writeLineData(std::vector<DebugDrawVertex>& vertexs, bool no_depth_test);
		void writeTriangleData(std::vector<DebugDrawVertex>& vertexs, bool no_depth_test);
		void writeUniformDynamicDataToCache(std::vector<std::pair<Matrix4x4, Vector4> >& datas);
		void writeTextData(std::vector<DebugDrawVertex>& vertexs, DebugDrawFont* font, Matrix4x4 m_proj_view_matrix);

		//增加物体
		void addPoint(const Vector3& position,const Vector4& color,const float life_time = k_debug_draw_one_frame,const bool no_depth_test = true);
		void addLine(const Vector3& point0,const Vector3& point1,const Vector4& color0,const Vector4& color1,const float life_time = k_debug_draw_one_frame,const bool no_depth_test = true);
		void addTriangle(const Vector3& point0,const Vector3& point1,const Vector3& point2,const Vector4& color0,const Vector4& color1,const Vector4& color2,const float life_time = k_debug_draw_one_frame,const bool no_depth_test = true,const FillMode fillmod = _FillMode_wireframe);
		void addQuad(const Vector3& point0,const Vector3& point1,const Vector3& point2,const Vector3& point3,const Vector4& color0,const Vector4& color1,const Vector4& color2,const Vector4& color3,const float life_time = k_debug_draw_one_frame,const bool no_depth_test = true,const FillMode fillmode = _FillMode_wireframe);
		void addBox(const Vector3& center_point,const Vector3& half_extends,const Vector4& rotate,const Vector4& color,const float life_time = k_debug_draw_one_frame,const bool no_depth_test = true);
		void addSphere(const Vector3& center,const float radius,const Vector4& color,const float life_time,const bool no_depth_test = true);
		void addCylinder(const Vector3& center,const float radius,const float height,const Vector4& rotate,const Vector4& color,const float life_time = k_debug_draw_one_frame,const bool no_depth_test = true);
		void addCapsule(const Vector3& center,const Vector4& rotation,const Vector3& scale,const float radius,const float height,const Vector4& color,const float life_time = k_debug_draw_one_frame,const bool no_depth_test = true);
		void addText(const std::string& content,const Vector4& color,const Vector3& coordinate,const int size,const bool is_screen_text,const float life_time = k_debug_draw_one_frame);

		void removeDeadPrimitives(float delta_time);

	private:
		std::mutex m_mutex;
		std::string m_name;//组名

		std::list<DebugDrawPoint>    m_points;
		std::list<DebugDrawLine>     m_lines;
		std::list<DebugDrawTriangle> m_triangles;
		std::list<DebugDrawQuad>     m_quads;
		std::list<DebugDrawBox>      m_boxes;
		std::list<DebugDrawCylinder> m_cylinders;
		std::list<DebugDrawSphere>   m_spheres;
		std::list<DebugDrawCapsule>  m_capsules;
		std::list<DebugDrawText>     m_texts;
	};
}