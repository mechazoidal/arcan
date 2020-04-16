/*
 *
 */
#ifndef HAVE_EGL_PROTOTYPES
#define HAVE_EGL_PROTOTYPES

#include "../EGL/egl.h"
#include "../EGL/eglext.h"

#if !defined(EGL_DRM_MASTER_FD_EXT)
#define EGL_DRM_MASTER_FD_EXT 0x333C
#endif

#if !defined(EGL_CONSUMER_AUTO_ACQUIRE_EXT)
#define EGL_CONSUMER_AUTO_ACQUIRE_EXT 0x332B
#endif

#if !defined(EGL_DRM_FLIP_EVENT_DATA_NV)
#define EGL_DRM_FLIP_EVENT_DATA_NV 0x33E
#endif

/*
 * Dynamically load all EGL function use, and look them up with dlsym if we're
 * dynamically linked against the EGL library already (for the devices where an
 * explicit library isn't defined). Since we synch a copy of the KHR EGL
 * headers there shouldn't be a conflict with the locally defined ones.
 */
typedef void* GLeglImageOES;
typedef void (EGLAPIENTRY* PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)(EGLenum target, GLeglImageOES image);
typedef EGLBoolean  (EGLAPIENTRY* PFNEGLCHOOSECONFIGPROC)(EGLDisplay dpy, const EGLint *attrib_list,	EGLConfig *configs, EGLint config_size,	EGLint *num_config);
typedef EGLContext  (EGLAPIENTRY* PFNEGLCREATECONTEXTPROC)(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list);
typedef EGLSurface  (EGLAPIENTRY* PFNEGLCREATEWINDOWSURFACEPROC)(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list);
typedef EGLint      (EGLAPIENTRY* PFNEGLGETERRORPROC)(void);
typedef EGLDisplay  (EGLAPIENTRY* PFNEGLGETDISPLAYPROC)(EGLNativeDisplayType display_id);
typedef void* (EGLAPIENTRY* PFNEGLGETPROCADDRESSPROC)(const char *procname);
typedef EGLBoolean  (EGLAPIENTRY* PFNEGLINITIALIZEPROC)
	(EGLDisplay dpy, EGLint *major, EGLint *minor);
typedef EGLBoolean  (EGLAPIENTRY* PFNEGLMAKECURRENTPROC)
	(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
typedef EGLBoolean  (EGLAPIENTRY* PFNEGLDESTROYCONTEXTPROC)
	(EGLDisplay dpy, EGLContext ctx);
typedef EGLBoolean  (EGLAPIENTRY* PFNEGLDESTROYSURFACEPROC)
	(EGLDisplay dpy, EGLSurface surface);
typedef const char* (EGLAPIENTRY* PGNEGLQUERYSTRINGPROC)
	(EGLDisplay dpy, EGLint name);
typedef EGLBoolean  (EGLAPIENTRY* PFNEGLSWAPBUFFERSPROC)
	(EGLDisplay dpy, EGLSurface surface);
typedef EGLBoolean  (EGLAPIENTRY* PFNEGLSWAPINTERVALPROC)
	(EGLDisplay dpy, EGLint interval);
typedef EGLBoolean  (EGLAPIENTRY* PFNEGLTERMINATEPROC)
	(EGLDisplay dpy);
typedef EGLBoolean (EGLAPIENTRY* PFNEGLBINDAPIPROC)(EGLenum);
typedef EGLBoolean (EGLAPIENTRY* PFNEGLGETCONFIGSPROC)
	(EGLDisplay, EGLConfig*, EGLint, EGLint*);
typedef const char* (EGLAPIENTRY* PFNEGLQUERYSTRINGPROC)(EGLDisplay, EGLenum);
typedef EGLBoolean (EGLAPIENTRY* PFNEGLSTREAMCONSUMERACQUIREATTRIBNVPROC)(EGLDisplay,
	EGLStreamKHR, const EGLAttrib*);
typedef EGLBoolean (EGLAPIENTRY* PFNEGLGETCONFIGATTRIBPROC)(EGLDisplay, EGLConfig, EGLint, EGLint*);

struct egl_env {
/* EGLImage */
	PFNEGLCREATEIMAGEKHRPROC create_image;
	PFNEGLDESTROYIMAGEKHRPROC destroy_image;
	PFNGLEGLIMAGETARGETTEXTURE2DOESPROC image_target_texture2D;

/* DMA-Buf */
	PFNEGLQUERYDMABUFFORMATSEXTPROC query_dmabuf_formats;
	PFNEGLQUERYDMABUFMODIFIERSEXTPROC query_dmabuf_modifiers;
	PFNEGLEXPORTDMABUFIMAGEMESAPROC export_dmabuf;
	PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC query_image_format;

/* EGLStreams */
	PFNEGLQUERYDEVICESEXTPROC query_devices;
	PFNEGLQUERYDEVICESTRINGEXTPROC query_device_string;
	PFNEGLGETPLATFORMDISPLAYEXTPROC get_platform_display;
	PFNEGLGETOUTPUTLAYERSEXTPROC get_output_layers;
	PFNEGLCREATESTREAMKHRPROC create_stream;
	PFNEGLDESTROYSTREAMKHRPROC destroy_stream;
	PFNEGLSTREAMCONSUMEROUTPUTEXTPROC stream_consumer_output;
	PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC create_stream_producer_surface;
	PFNEGLSTREAMCONSUMERACQUIREKHRPROC stream_consumer_acquire;
	PFNEGLSTREAMCONSUMERACQUIREATTRIBNVPROC stream_consumer_acquire_attrib;

/* Basic EGL */
	PFNEGLDESTROYSURFACEPROC destroy_surface;
	PFNEGLGETERRORPROC get_error;
	PFNEGLCREATEWINDOWSURFACEPROC create_window_surface;
	PFNEGLMAKECURRENTPROC make_current;
	PFNEGLGETDISPLAYPROC get_display;
	PFNEGLINITIALIZEPROC initialize;
	PFNEGLBINDAPIPROC bind_api;
	PFNEGLGETCONFIGSPROC get_configs;
	PFNEGLCHOOSECONFIGPROC choose_config;
	PFNEGLCREATECONTEXTPROC create_context;
	PFNEGLGETPROCADDRESSPROC get_proc_address;
	PFNEGLDESTROYCONTEXTPROC destroy_context;
	PFNEGLTERMINATEPROC terminate;
	PFNEGLQUERYSTRINGPROC query_string;
	PFNEGLSWAPBUFFERSPROC swap_buffers;
	PFNEGLSWAPINTERVALPROC swap_interval;
	PFNEGLGETCONFIGATTRIBPROC get_config_attrib;
};

static void map_eglext_functions(struct egl_env* denv,
	void*(lookup)(void* tag, const char* sym, bool req), void* tag)
{
/* Mapping dma_buf */
/* XXX: */
	denv->create_image = (PFNEGLCREATEIMAGEKHRPROC)
		lookup(tag, "eglCreateImageKHR", false);
/* XXX: */
	denv->destroy_image = (PFNEGLDESTROYIMAGEKHRPROC)
		lookup(tag, "eglDestroyImageKHR", false);
/* XXX: */
	denv->image_target_texture2D = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)
		lookup(tag, "glEGLImageTargetTexture2DOES", false);

/* EGL_EXT_image_dma_buf_import_modifiers */
	denv->query_dmabuf_modifiers = (PFNEGLQUERYDMABUFMODIFIERSEXTPROC)
		lookup(tag, "eglQueryDmaBufModifiersEXT", false);
	denv->query_dmabuf_formats = (PFNEGLQUERYDMABUFFORMATSEXTPROC)
		lookup(tag, "eglQueryDmaBufFormatsEXT", false);
	denv->query_image_format = (PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC)
		lookup(tag, "eglExportDMABUFImageQueryMESA", false);
	denv->export_dmabuf = (PFNEGLEXPORTDMABUFIMAGEMESAPROC)
		lookup(tag, "eglExportDMABUFImageMESA", false);

/* EGLStreams */
/* "EGL_EXT_device_query"
 * "EGL_EXT_device_enumeration"
 * "EGL_EXT_device_query" */

	denv->query_device_string = (PFNEGLQUERYDEVICESTRINGEXTPROC)
		lookup(tag, "eglQueryDeviceStringEXT", false);
	denv->query_devices = (PFNEGLQUERYDEVICESEXTPROC)
		lookup(tag, "eglQueryDevicesEXT", false);
	denv->get_platform_display = (PFNEGLGETPLATFORMDISPLAYEXTPROC)
		lookup(tag, "eglGetPlatformDisplayEXT", false );
	denv->get_output_layers = (PFNEGLGETOUTPUTLAYERSEXTPROC)
		lookup(tag, "eglGetOutputLayersEXT", false);
	denv->create_stream = (PFNEGLCREATESTREAMKHRPROC)
		lookup(tag, "eglCreateStreamKHR", false);
	denv->destroy_stream = (PFNEGLDESTROYSTREAMKHRPROC)
		lookup(tag, "eglDestroyStreamKHR", false);
  denv->stream_consumer_output = (PFNEGLSTREAMCONSUMEROUTPUTEXTPROC)
		lookup(tag, "eglStreamConsumerOutputEXT", false);
	denv->create_stream_producer_surface = (PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC)
		lookup(tag, "eglCreateStreamProducerSurfaceKHR", false);
	denv->stream_consumer_acquire = (PFNEGLSTREAMCONSUMERACQUIREKHRPROC)
		lookup(tag, "eglStreamConsumerAcquireKHR", false);
	denv->stream_consumer_acquire_attrib = (PFNEGLSTREAMCONSUMERACQUIREATTRIBNVPROC)
		lookup(tag, "eglStreamConsumerAcquireAttribNV", false);
}

static void map_egl_functions(struct egl_env* denv,
	void*(lookup)(void* tag, const char* sym, bool req), void* tag)
{
	denv->get_config_attrib =
		(PFNEGLGETCONFIGATTRIBPROC) lookup(tag, "eglGetConfigAttrib", true);
	denv->destroy_surface =
		(PFNEGLDESTROYSURFACEPROC) lookup(tag, "eglDestroySurface", true);
	denv->get_error =
		(PFNEGLGETERRORPROC) lookup(tag, "eglGetError", true);
	denv->create_window_surface =
		(PFNEGLCREATEWINDOWSURFACEPROC) lookup(tag, "eglCreateWindowSurface", true);
	denv->make_current =
		(PFNEGLMAKECURRENTPROC) lookup(tag, "eglMakeCurrent", true);
	denv->get_display =
		(PFNEGLGETDISPLAYPROC) lookup(tag, "eglGetDisplay", true);
	denv->initialize =
		(PFNEGLINITIALIZEPROC) lookup(tag, "eglInitialize", true);
	denv->bind_api =
		(PFNEGLBINDAPIPROC) lookup(tag, "eglBindAPI", true);
	denv->get_configs =
		(PFNEGLGETCONFIGSPROC) lookup(tag, "eglGetConfigs", true);
	denv->choose_config =
		(PFNEGLCHOOSECONFIGPROC) lookup(tag, "eglChooseConfig", true);
	denv->create_context =
		(PFNEGLCREATECONTEXTPROC) lookup(tag, "eglCreateContext", true);
	denv->destroy_context =
		(PFNEGLDESTROYCONTEXTPROC) lookup(tag, "eglDestroyContext", true);
	denv->terminate = (PFNEGLTERMINATEPROC) lookup(tag, "eglTerminate", true);
	denv->query_string =
		(PFNEGLQUERYSTRINGPROC) lookup(tag, "eglQueryString", true);
	denv->swap_buffers =
		(PFNEGLSWAPBUFFERSPROC) lookup(tag, "eglSwapBuffers", true);
	denv->swap_interval =
		(PFNEGLSWAPINTERVALPROC) lookup(tag, "eglSwapInterval", true);
}

#endif
