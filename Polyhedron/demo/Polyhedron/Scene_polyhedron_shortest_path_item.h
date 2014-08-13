#ifndef SCENE_POLYHEDRON_SHORTEST_PATH_ITEM_H
#define SCENE_POLYHEDRON_SHORTEST_PATH_ITEM_H

#include "Scene_polyhedron_shortest_path_item_config.h"
#include "Scene_polyhedron_item_decorator.h"
#include "Scene_interface.h"
#include "Messages_interface.h"

#include "Polyhedron_type.h"
#include "Kernel_type.h"

#include "opengl_tools.h"
#include <CGAL/gl_render.h>

#include <QGLViewer/qglviewer.h>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMainWindow>
#include <QObject>

#include <string>
#include <list>

#ifndef Q_MOC_RUN
#include <CGAL/Polyhedron_shortest_path/Polyhedron_shortest_path.h>
#include <CGAL/Polyhedron_shortest_path/Polyhedron_shortest_path_traits.h>
#endif

#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_tree.h>

#include <boost/current_function.hpp>

class SCENE_POLYHEDRON_SHORTEST_PATH_ITEM_EXPORT Scene_polyhedron_shortest_path_item : public Scene_polyhedron_item_decorator
{
  Q_OBJECT
  
  friend class Polyhedron_demo_shortest_path_plugin;
  
public:
  typedef Scene_interface::Bbox Bbox;

  typedef boost::property_map<Polyhedron, boost::vertex_index_t>::type VertexIndexMap;
  typedef boost::property_map<Polyhedron, CGAL::halfedge_index_t>::type HalfedgeIndexMap;
  typedef boost::property_map<Polyhedron, CGAL::face_index_t>::type FaceIndexMap;
  typedef boost::property_map<Polyhedron, CGAL::vertex_point_t>::type VertexPointMap;
  
  typedef boost::graph_traits<Polyhedron> GraphTraits;
  typedef GraphTraits::face_descriptor face_descriptor;
  typedef GraphTraits::face_iterator face_iterator;
  
  typedef CGAL::Polyhedron_shortest_path_default_traits<Kernel, Polyhedron> Polyhedron_shortest_path_traits;
  typedef CGAL::Polyhedron_shortest_path<Polyhedron_shortest_path_traits, VertexIndexMap, HalfedgeIndexMap, FaceIndexMap, VertexPointMap> Polyhedron_shortest_path;
  typedef Polyhedron_shortest_path::Face_location Face_location;
  typedef CGAL::AABB_face_graph_triangle_primitive<Polyhedron, VertexPointMap> AABB_face_graph_primitive;
  typedef CGAL::AABB_traits<Kernel, AABB_face_graph_primitive> AABB_face_graph_traits;
  typedef CGAL::AABB_tree<AABB_face_graph_traits> AABB_face_graph_tree;
  
  typedef Polyhedron_shortest_path_traits::Barycentric_coordinate Barycentric_coordinate;
  typedef Polyhedron_shortest_path_traits::Ray_3 Ray_3;
  typedef Polyhedron_shortest_path_traits::Point_3 Point_3;
  typedef Polyhedron_shortest_path_traits::FT FT;
  
  enum Selection_mode
  {
    INSERT_POINTS_MODE = 0,
    REMOVE_POINTS_MODE = 1,
    SHORTEST_PATH_MODE = 2,
  };
  
  enum Primitives_mode
  {
    VERTEX_MODE = 0,
    EDGE_MODE = 1,
    FACE_MODE = 2,
  };
  
  typedef std::list<Face_location> Face_locations;
  
private:
  Messages_interface* m_messages;
  QMainWindow* m_mainWindow;
  Scene_interface* m_sceneInterface;
  Polyhedron_shortest_path* m_shortestPaths;
  AABB_face_graph_tree m_aabbTree;
  
  std::string m_deferredLoadFilename;
  
  Selection_mode m_selectionMode;
  Primitives_mode m_primitivesMode;
  
  Face_locations m_faceLocations;
  
  bool m_isComputed;
  bool m_isTreeCached;
  
  bool m_shiftHeld;
  
private:
  bool get_mouse_ray(QMouseEvent* mouseEvent, Kernel::Ray_3&);

  void recreate_shortest_path_object();
  void ensure_aabb_object();
  void ensure_shortest_paths_tree();
  
  bool run_point_select(const Kernel::Ray_3&);
  void remove_nearest_point(const Face_location& ray);
  void get_as_edge_point(Face_location& inOutLocation);
  void get_as_vertex_point(Face_location& inOutLocation);
  
  
public:

  Scene_polyhedron_shortest_path_item();
  Scene_polyhedron_shortest_path_item(Scene_polyhedron_item* polyhedronItem, Scene_interface* sceneInterface, Messages_interface* messages, QMainWindow* mainWindow);
  ~Scene_polyhedron_shortest_path_item();
  
  void set_selection_mode(Selection_mode mode);
  Selection_mode get_selection_mode() const;
  void set_primitives_mode(Primitives_mode mode);
  Primitives_mode get_primitives_mode() const;
  
  virtual bool supportsRenderingMode(RenderingMode m) const;
  virtual void draw() const;
  virtual void draw(Viewer_interface*) const;
  // Wireframe OpenGL drawing
  virtual void draw_edges() const;
  virtual void draw_edges(Viewer_interface*) const;
  // Points OpenGL drawing
  virtual void draw_points() const;
  virtual void draw_points(Viewer_interface*) const;
  
  virtual Scene_polyhedron_shortest_path_item* clone() const;
  
  bool deferred_load(Scene_polyhedron_item* polyhedronItem, Scene_interface* sceneInterface, Messages_interface* messages, QMainWindow* mainWindow);
  virtual bool load(const std::string& file_name);
  virtual bool save(const std::string& file_name) const;
  
protected:
  void initialize(Scene_polyhedron_item* polyhedronItem, Scene_interface* sceneInterface, Messages_interface* messages, QMainWindow* mainWindow);
  void deinitialize();
  
  virtual bool isFinite() const;
  virtual bool isEmpty() const;
  virtual Bbox bbox() const;
  virtual QString toolTip() const;
  
protected:
  bool eventFilter(QObject* /*target*/, QEvent * gen_event);
  
public slots:
  virtual void poly_item_changed();
  virtual void changed();
};

#endif // SCENE_POLYHEDRON_SHORTEST_PATH_ITEM_H
