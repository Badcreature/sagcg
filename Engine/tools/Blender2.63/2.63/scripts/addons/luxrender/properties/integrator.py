# -*- coding: utf8 -*-
#
# ***** BEGIN GPL LICENSE BLOCK *****
#
# --------------------------------------------------------------------------
# Blender 2.5 LuxRender Add-On
# --------------------------------------------------------------------------
#
# Authors:
# Doug Hammond
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.
#
# ***** END GPL LICENCE BLOCK *****
#
from extensions_framework import declarative_property_group
from extensions_framework.validate import Logic_OR as O, Logic_Operator as LO

from .. import LuxRenderAddon
from ..export import ParamSet
from ..outputs import LuxLog
from ..outputs.pure_api import LUXRENDER_VERSION
#from .engine import check_renderer_settings

@LuxRenderAddon.addon_register_class
class luxrender_volumeintegrator(declarative_property_group):
	'''
	Storage class for LuxRender Volume Integrator settings.
	'''
	
	ef_attach_to = ['Scene']
	
	controls = [
		[0.7, 'volumeintegrator', 'advanced'],
		'stepsize',
	]
	
	visibility = {
		'stepsize':							{ 'advanced': True },
	}
	
	properties = [
		{
			'type': 'enum',
			'attr': 'volumeintegrator',
			'name': 'Volume Integrator',
			'description': 'Volume Integrator',
			'default': 'multi',
			'items': [
				('emission', 'Emission', 'Calculate absorption and light-emission only'),
				('single', 'Single', 'Calculate single scattering as well as absorption and light-emission'),
				('multi', 'Multi', 'Calculate all volumetric effects, including multiple scattering, absorption, and light-emission'),
			],
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'stepsize',
			'name': 'Step Size',
			'description': 'Ray-marching step size. Only used for smoke simulations',
			'default': 1.0,
			'min': 0.0,
			'soft_min': 0.0,
			'max': 100.0,
			'soft_max': 100.0,
			'sub_type': 'DISTANCE',
			'unit': 'LENGTH',
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'advanced',
			'name': 'Advanced',
			'description': 'Configure advanced volume integrator settings',
			'default': False,
			'save_in_preset': True
		},
	]
	
	def api_output(self):
		'''
		Format this class's members into a LuxRender ParamSet
		
		Returns dict
		'''
		
		params = ParamSet()
		
		params.add_float('stepsize', self.stepsize)
		
		return self.volumeintegrator, params

@LuxRenderAddon.addon_register_class
class luxrender_integrator(declarative_property_group):
	'''
	Storage class for LuxRender SurfaceIntegrator settings.
	'''
	
	ef_attach_to = ['Scene']
	
	controls = [
		'advanced',
		'lightstrategy',
		
		# bidir +
		['eyedepth', 'lightdepth'],
		['eyerrthreshold', 'lightrrthreshold'],
		
		# dl +
		'maxdepth',
		
		# dp
		['lbl_direct',
		'directsamples'],
		['directsampleall',
		'directdiffuse',
		'directglossy'],
		['lbl_indirect',
		'indirectsamples'],
		['indirectsampleall',
		'indirectdiffuse',
		'indirectglossy'],
		'lbl_diffuse',
		['diffusereflectsamples',
		'diffusereflectdepth'],
		['diffuserefractsamples',
		'diffuserefractdepth'],
		'lbl_glossy',
		['glossyreflectsamples',
		'glossyreflectdepth'],
		['glossyrefractsamples',
		'glossyrefractdepth'],
		'lbl_specular',
		['specularreflectdepth',
		'specularrefractdepth'],
		'lbl_rejection',
		['diffusereflectreject',
		'diffusereflectreject_threshold'],
		['diffuserefractreject',
		'diffuserefractreject_threshold'],
		['glossyreflectreject',
		'glossyreflectreject_threshold'],
		['glossyrefractreject',
		'glossyrefractreject_threshold'],
		
		# epm
		['maxeyedepth', 'maxphotondepth'],
		#Exphotonmap uses maxdepth, not maxeyedepth. However, it uses maxeyedepth in the GUI to allow a double-box for both itself and SPPM
		#This is because maxdepth cannot be used in a double box, since path, igi, and direct use maxdepth by itself.
		#The value of maxeyedepth is exported for the "maxdepth" entry in the lxs when using exphotonmap, see export section
		'directphotons',
		'causticphotons',
		'indirectphotons',
		'radiancephotons',
		'nphotonsused',
		'maxphotondist',
		'renderingmode',
		'finalgather',
		'finalgathersamples',
		'gatherangle',
		'distancethreshold',
		'rrstrategy',
		'rrcontinueprob',
		# epm advanced
		'photonmapsfile',
		# epm debug
		'debugmode',
		'dbg_enabledirect',
		'dbg_enableradiancemap',
		'dbg_enableindircaustic',
		'dbg_enableindirdiffuse',
		'dbg_enableindirspecular',
		
		# igi
		'nsets',
		'nlights',
		'mindist',
		
		#sppm
		'photonperpass',
		['startradius', 'alpha'],
		'sppmdirectlight',
		#sppm advanced
		'glossythreshold',
		'wavelengthstratificationpasses',
		'lookupaccel',
		'parallelhashgridspare',
		'pixelsampler',
		'photonsampler',
		'useproba',
				
		# path
		'shadowraycount',
		'directlightsampling',
		'includeenvironment',
	]
	
	visibility = {
		# bidir +
		'eyedepth':							{ 'surfaceintegrator': 'bidirectional' },
		'lightdepth':						{ 'surfaceintegrator': 'bidirectional' },
		'eyerrthreshold':					{ 'advanced': True, 'surfaceintegrator': 'bidirectional' },
		'lightrrthreshold':					{ 'advanced': True, 'surfaceintegrator': 'bidirectional' },
		'lightstrategy':					{ 'advanced': True, 'surfaceintegrator': O(['directlighting', 'exphotonmap', 'igi', 'path',  'distributedpath', 'bidirectional'])},
		
		# dl +
		'maxdepth':							{ 'surfaceintegrator': O(['directlighting', 'igi', 'path']) },
		
		# dp
		'lbl_direct':						{ 'surfaceintegrator': 'distributedpath' },
		'directsampleall':					{ 'advanced': True, 'surfaceintegrator': 'distributedpath' },
		'directsamples':					{ 'surfaceintegrator': 'distributedpath' },
		'directdiffuse':					{ 'advanced': True, 'surfaceintegrator': 'distributedpath' },
		'directglossy':						{ 'advanced': True, 'surfaceintegrator': 'distributedpath' },
		'lbl_indirect':						{ 'surfaceintegrator': 'distributedpath' },
		'indirectsampleall':				{ 'advanced': True, 'surfaceintegrator': 'distributedpath' },
		'indirectsamples':					{ 'surfaceintegrator': 'distributedpath' },
		'indirectdiffuse':					{ 'advanced': True, 'surfaceintegrator': 'distributedpath' },
		'indirectglossy':					{ 'advanced': True, 'surfaceintegrator': 'distributedpath' },
		'lbl_diffuse':						{ 'surfaceintegrator': 'distributedpath' },
		'diffusereflectdepth':				{ 'surfaceintegrator': 'distributedpath' },
		'diffusereflectsamples':			{ 'surfaceintegrator': 'distributedpath' },
		'diffuserefractdepth':				{ 'surfaceintegrator': 'distributedpath' },
		'diffuserefractsamples':			{ 'surfaceintegrator': 'distributedpath' },
		'lbl_glossy':						{ 'surfaceintegrator': 'distributedpath' },
		'glossyreflectdepth':				{ 'surfaceintegrator': 'distributedpath' },
		'glossyreflectsamples':				{ 'surfaceintegrator': 'distributedpath' },
		'glossyrefractdepth':				{ 'surfaceintegrator': 'distributedpath' },
		'glossyrefractsamples':				{ 'surfaceintegrator': 'distributedpath' },
		'lbl_specular':						{ 'surfaceintegrator': 'distributedpath' },
		'specularreflectdepth':				{ 'surfaceintegrator': 'distributedpath' },
		'specularrefractdepth':				{ 'surfaceintegrator': 'distributedpath' },
		'lbl_rejection':					{ 'advanced': True, 'surfaceintegrator': 'distributedpath' },
		'diffusereflectreject':				{ 'advanced': True, 'surfaceintegrator': 'distributedpath' },
		'diffusereflectreject_threshold':	{ 'advanced': True, 'diffusereflectreject': True, 'surfaceintegrator': 'distributedpath' },
		'diffuserefractreject':				{ 'advanced': True, 'surfaceintegrator': 'distributedpath' },
		'diffuserefractreject_threshold':	{ 'advanced': True, 'diffuserefractreject': True, 'surfaceintegrator': 'distributedpath' },
		'glossyreflectreject':				{ 'advanced': True, 'surfaceintegrator': 'distributedpath' },
		'glossyreflectreject_threshold':	{ 'advanced': True, 'glossyreflectreject': True, 'surfaceintegrator': 'distributedpath' },
		'glossyrefractreject':				{ 'advanced': True, 'surfaceintegrator': 'distributedpath' },
		'glossyrefractreject_threshold':	{ 'advanced': True, 'glossyrefractreject': True, 'surfaceintegrator': 'distributedpath' },
		
		# expm
		'maxeyedepth':						{ 'surfaceintegrator': O(['exphotonmap', 'sppm']) },
		'maxphotondepth':					{ 'surfaceintegrator': O(['exphotonmap', 'sppm']) },
		'directphotons':					{ 'surfaceintegrator': 'exphotonmap' },
		'causticphotons':					{ 'surfaceintegrator': 'exphotonmap' },
		'indirectphotons':					{ 'surfaceintegrator': 'exphotonmap' },
		'radiancephotons':					{ 'surfaceintegrator': 'exphotonmap' },
		'nphotonsused':						{ 'surfaceintegrator': 'exphotonmap' },
		'maxphotondist':					{ 'surfaceintegrator': 'exphotonmap' },
		'renderingmode':					{ 'surfaceintegrator': 'exphotonmap' },
		'finalgather':						{ 'renderingmode': 'directlighting', 'surfaceintegrator': 'exphotonmap' },
		'finalgathersamples':				{ 'finalgather': True, 'renderingmode': 'directlighting', 'surfaceintegrator': 'exphotonmap' },
		'gatherangle':						{ 'finalgather': True, 'renderingmode': 'directlighting', 'surfaceintegrator': 'exphotonmap' },
		'rrstrategy':						{ 'surfaceintegrator': O(['exphotonmap', 'path']) },
		'rrcontinueprob':					{ 'rrstrategy': 'probability', 'surfaceintegrator': O(['exphotonmap', 'path']) },
		'distancethreshold':				{ 'renderingmode': 'path', 'surfaceintegrator': 'exphotonmap' },
		# expm advanced
		'photonmapsfile':					{ 'advanced': True, 'surfaceintegrator': 'exphotonmap' },
		
		# expm debug
		'debugmode':						{ 'surfaceintegrator': 'exphotonmap' },
		'dbg_enabledirect':					{ 'debugmode': True, 'surfaceintegrator': 'exphotonmap' },
		'dbg_enableradiancemap':			{ 'debugmode': True, 'surfaceintegrator': 'exphotonmap' },
		'dbg_enableindircaustic':			{ 'debugmode': True, 'surfaceintegrator': 'exphotonmap' },
		'dbg_enableindirdiffuse':			{ 'debugmode': True, 'surfaceintegrator': 'exphotonmap' },
		'dbg_enableindirspecular':			{ 'debugmode': True, 'surfaceintegrator': 'exphotonmap' },
		
		# igi
		'nsets':							{ 'surfaceintegrator': 'igi' },
		'nlights':							{ 'surfaceintegrator': 'igi' },
		'mindist':							{ 'surfaceintegrator': 'igi' },
		
		# path
		'includeenvironment':				{ 'surfaceintegrator': O(['sppm', 'path']) },
		'directlightsampling':				{ 'surfaceintegrator': 'path' },
		'shadowraycount':					{ 'advanced': True, 'surfaceintegrator': 'path' },
		
		# sppm
		'photonperpass':					{ 'surfaceintegrator': 'sppm' },
		'startk':							{ 'surfaceintegrator': 'sppm' },
		'alpha':							{ 'surfaceintegrator': 'sppm' },
		'startradius':						{ 'surfaceintegrator': 'sppm' },
		'sppmdirectlight':					{ 'surfaceintegrator': 'sppm' },

		# sppm advanced
		'glossythreshold':					{ 'advanced': True, 'surfaceintegrator': 'sppm' },
		'wavelengthstratificationpasses': 	{ 'advanced': True, 'surfaceintegrator': 'sppm' },
		'lookupaccel':						{ 'advanced': True, 'surfaceintegrator': 'sppm' },
		'parallelhashgridspare':			{ 'advanced': True, 'lookupaccel': 'parallelhashgrid', 'surfaceintegrator': 'sppm' },
		'pixelsampler':						{ 'advanced': True, 'surfaceintegrator': 'sppm' },
		'photonsampler':					{ 'advanced': True, 'surfaceintegrator': 'sppm' },
		'useproba':						{ 'advanced': True, 'surfaceintegrator': 'sppm' },
	}
	
	alert = {}
	
	properties = [
		#This parameter is fed to the "integrator' context, and holds the actual surface integrator setting. The user does not interact with it directly, and it does not appear in the panels
		{
			'type': 'enum', 
			'attr': 'surfaceintegrator',
			'name': 'Surface Integrator',
			'description': 'Surface Integrator',
			'default': 'bidirectional',
			'items': [
				('bidirectional', 'Bidirectional', 'bidirectional'),
				('path', 'Path', 'path'),
				('directlighting', 'Direct Lighting', 'directlighting'),
				('distributedpath', 'Distributed Path', 'distributedpath'),
				('igi', 'Instant Global Illumination', 'igi',),
				('exphotonmap', 'Ex-Photon Map', 'exphotonmap'),
				('sppm', 'SPPM', 'sppm'),
			],
			#'update': lambda s,c: check_renderer_settings(c),
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'advanced',
			'name': 'Advanced',
			'description': 'Configure advanced integrator settings',
			'default': False,
			#'update': lambda s,c: check_renderer_settings(c),
			'save_in_preset': True
		},
		{
			'type': 'enum',
			'attr': 'lightstrategy',
			'name': 'Light Strategy',
			'description': 'Light Sampling Strategy',
			'default': 'auto',
			'items': [
				('auto', 'Auto', 'auto'),
				('one', 'One', 'one'),
				('all', 'All', 'all'),
				('importance', 'Importance', 'importance'),
				('powerimp', 'Power', 'powerimp'),
				('allpowerimp', 'All Power', 'allpowerimp'),
				('logpowerimp', 'Log Power', 'logpowerimp')
			],
			#'update': lambda s,c: check_renderer_settings(c),
			'save_in_preset': True
		},
		{
			'type': 'int', 
			'attr': 'eyedepth',
			'name': 'Eye Depth',
			'description': 'Max recursion depth for ray casting from eye',
			'default': 48,
			'min': 1,
			'max': 2048,
			'save_in_preset': True
		},
		{
			'type': 'int', 
			'attr': 'lightdepth',
			'name': 'Light Depth',
			'description': 'Max recursion depth for ray casting from light',
			'default': 48,
			'min': 1,
			'max': 2048,
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'eyerrthreshold',
			'name': 'Eye RR Threshold',
			'default': 0.0,
			'min': 0.0,
			'max': 1.0,
			'slider': True,
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'lightrrthreshold',
			'name': 'Light RR Threshold',
			'default': 0.0,
			'min': 0.0,
			'max': 1.0,
			'slider': True,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'maxdepth',
			'name': 'Max. depth',
			'description': 'Max recursion depth for ray casting from eye',
			'default': 48,
			'min': 1,
			'max': 2048,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'shadowraycount',
			'name': 'Shadow Ray Count',
			'default': 1,
			'save_in_preset': True
		},
		{
			'type': 'text',
			'attr': 'lbl_direct',
			'name': 'Direct light sampling',
		},
		{
			'type': 'bool',
			'attr': 'directsampleall',
			'name': 'Sample all',
			'default': True,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'directsamples',
			'name': 'Samples',
			'default': 1,
			'description': 'Number of shadow rays to start from first path vertex',
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'directdiffuse',
			'name': 'Diffuse',
			'default': True,
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'directglossy',
			'name': 'Glossy',
			'default': True,
			'save_in_preset': True
		},
		
		{
			'type': 'text',
			'attr': 'lbl_indirect',
			'name': 'Indirect light sampling',
		},
		{
			'type': 'bool',
			'attr': 'indirectsampleall',
			'name': 'Sample all',
			'default': False,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'indirectsamples',
			'name': 'Samples',
			'default': 1,
			'description': 'Number of shadows rays to start from subsequent path vertices',
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'indirectdiffuse',
			'name': 'Diffuse',
			'default': True,
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'indirectglossy',
			'name': 'Glossy',
			'default': True,
			'save_in_preset': True
		},
		
		{
			'type': 'text',
			'attr': 'lbl_diffuse',
			'name': 'Diffuse settings',
		},
		{
			'type': 'int',
			'attr': 'diffusereflectdepth',
			'name': 'Reflection depth',
			'description': 'Max recursion depth after bouncing from a diffuse surface',
			'default': 3,
			'min': 0,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'diffusereflectsamples',
			'name': 'Reflection samples',
			'description': 'Number of paths to start from a diffuse-reflection vertex',
			'default': 1,
			'min': 0,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'diffuserefractdepth',
			'name': 'Refraction depth',
			'description': 'Max recursion depth after bouncing through a diffuse-refraction (translucent) surface',
			'default': 5,
			'min': 0,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'diffuserefractsamples',
			'name': 'Refraction samples',
			'description': 'Number of paths to start from a diffuse-refraction (translucent) vertex',
			'default': 1,
			'min': 0,
			'save_in_preset': True
		},
		
		{
			'type': 'text',
			'attr': 'lbl_glossy',
			'name': 'Glossy settings',
		},
		{
			'type': 'int',
			'attr': 'glossyreflectdepth',
			'name': 'Reflection depth',
			'description': 'Max recursion depth after bouncing from a glossy surface',
			'default': 2,
			'min': 0,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'glossyreflectsamples',
			'name': 'Reflection samples',
			'description': 'Number of paths to start from a glossy-reflection vertex',
			'default': 1,
			'min': 0,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'glossyrefractdepth',
			'name': 'Refraction depth',
			'description': 'Max recursion depth after bouncing through a glossy-refraction surface, such as rough glass',
			'default': 5,
			'min': 0,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'glossyrefractsamples',
			'name': 'Refraction samples',
			'description': 'Number of paths to start from a glossy-refraction vertex, such as rough glass',
			'default': 1,
			'min': 0,
			'save_in_preset': True
		},
		
		{
			'type': 'text',
			'attr': 'lbl_specular',
			'name': 'Specular settings',
		},
		{
			'type': 'int',
			'attr': 'specularreflectdepth',
			'name': 'Reflection depth',
			'description': 'Max recursion depth after a specular reflection',
			'default': 3,
			'min': 0,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'specularrefractdepth',
			'name': 'Refraction depth',
			'description': 'Max recursion depth after a specular transmission, such as glass or null',
			'default': 5,
			'min': 0,
			'save_in_preset': True
		},
		
		{
			'type': 'text',
			'attr': 'lbl_rejection',
			'name': 'Rejection settings',
		},
		{
			'type': 'bool',
			'attr': 'diffusereflectreject',
			'name': 'Diffuse reflection reject',
			'default': False,
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'diffusereflectreject_threshold',
			'name': 'Threshold',
			'default': 10.0,
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'diffuserefractreject',
			'name': 'Diffuse refraction reject',
			'default': False,
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'diffuserefractreject_threshold',
			'name': 'Threshold',
			'default': 10.0,
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'glossyreflectreject',
			'name': 'Glossy reflection reject',
			'default': False,
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'glossyreflectreject_threshold',
			'name': 'Threshold',
			'default': 10.0,
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'glossyrefractreject',
			'name': 'Glossy refraction reject',
			'default': False,
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'glossyrefractreject_threshold',
			'name': 'Threshold',
			'default': 10.0,
			'save_in_preset': True
		},
		
		{
			'type': 'int',
			'attr': 'maxphotondepth',
			'name': 'Max. photon depth',
			'description': 'Max recursion depth for photon tracing',
			'default': 48,
			'min': 1,
			'max': 2048,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'directphotons',
			'name': 'Direct photons',
			'description': 'Target number of direct light photons',
			'default': 1000000,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'causticphotons',
			'name': 'Caustic photons',
			'description': 'Target number of caustic photons',
			'default': 20000,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'indirectphotons',
			'name': 'Indirect photons',
			'description': 'Target number of soft-indirect photons',
			'default': 200000,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'radiancephotons',
			'name': 'Radiance photons',
			'description': 'Target number of final gather photons',
			'default': 200000,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'nphotonsused',
			'name': 'Number of photons used',
			'default': 50,
			'min': 1,
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'maxphotondist',
			'name': 'Max. photon distance',
			'default': 0.1,
			'min': 0.01,
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'finalgather',
			'name': 'Final Gather',
			'default': True,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'finalgathersamples',
			'name': 'Final gather samples',
			'description': 'Number of final gather samples to shoot for each ray',
			'default': 32,
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'gatherangle',
			'name': 'Gather angle',
			'description': 'Reject final gather rays beyond this angle. Adjusts final gather accuracy',
			'default': 10.0,
			'save_in_preset': True
		},
		{
			'type': 'enum',
			'attr': 'renderingmode',
			'name': 'Eye-Pass Mode',
			'default': 'directlighting',
			'items': [
				('directlighting', 'Direct Lighting', 'directlighting'),
				('path', 'Path', 'path'),
			],
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'distancethreshold',
			'name': 'Distance threshold',
			'description': 'Fallbacks to path tracing when rendering corners in order to avoid photon leaks', #<--- that's what the wiki says it does.
			'default': 0.5, #same as maxphotondist, this is how core defaults according to wiki
			'save_in_preset': True
		},
		{
			'type': 'string',
			'subtype': 'FILE_PATH',
			'attr': 'photonmapsfile',
			'name': 'Photonmaps file',
			'default': '',
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'debugmode',
			'name': 'Enable Debug Mode',
			'default': False,
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'dbg_enabledirect',
			'name': 'Debug: Enable direct',
			'default': True,
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'dbg_enableradiancemap',
			'name': 'Debug: Enable radiance map',
			'default': False,
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'dbg_enableindircaustic',
			'name': 'Debug: Enable indirect caustics',
			'default': True,
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'dbg_enableindirdiffuse',
			'name': 'Debug: Enable indirect diffuse',
			'default': True,
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'dbg_enableindirspecular',
			'name': 'Debug: Enable indirect specular',
			'default': True,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'nsets',
			'name': 'Number of sets',
			'default': 4,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'nlights',
			'name': 'Number of lights',
			'default': 64,
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'mindist',
			'name': 'Min. Distance',
			'default': 0.1,
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'rrcontinueprob',
			'name': 'RR continue probability',
			'default': 0.65,
			'min': 0.0,
			'max': 1.0,
			'slider': True,
			'save_in_preset': True
		},
		{
			'type': 'enum',
			'attr': 'rrstrategy',
			'name': 'RR strategy',
			'default': 'efficiency',
			'items': [
				('efficiency', 'Efficiency', 'efficiency'),
				('probability', 'Probability', 'probability'),
				('none', 'None', 'none'),
			],
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'includeenvironment',
			'name': 'Include Environment',
			'default': True,
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'directlightsampling',
			'name': 'Direct Light Sampling',
			'description': 'Turn this off to use brute force path tracing (faster with only "infinite" light (HDRI))',
			'default': True,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'maxeyedepth',
			'name': 'Max. eye depth',
			'default': 48,
			'description': 'Max recursion depth for ray casting from eye',
			'min': 1,
			'max': 2048,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'photonperpass',
			'name': 'Photons per pass',
			'description': 'Number of photons to gather before going on to next pass',
			'default': 1000000,
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'startradius',
			'name': 'Starting radius',
			'description': 'Photon radius used for initial pass. Try lowering this if the first pass renders very slowly',
			'default': 2.0,
			'min': 0.0001,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'startk',
			'name': 'Starting K',
			'description': 'Adjust starting photon radius to get this many photons. Higher values clear faster but are less accurate. 0=use initial radius',
			'default': 30,
			'min': 0,
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'alpha',
			'name': 'Alpha',
			'description': 'Tighten photon search radius by this factor on subsequent passes',
			'default': 0.7,
			'min': 0.01,
			'max': 1.0,
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'glossythreshold',
			'name': 'Glossy Threshold',
			'description': 'Maximum specularity (PDF) that will store photons. 0=only matte materials store photons',
			'min': 0,
			'default': 100,
			'save_in_preset': True
		},
		{
			'type': 'enum',
			'attr': 'lookupaccel',
			'name': 'Lookup accelerator',
			'description': 'Acceleration structure for hitpoints (not scene geometry)',
			'default': 'hybridhashgrid',
			'items': [
				('hashgrid', 'Hash Grid', 'hashgrid'),
				('kdtree', 'KD Tree', 'kdtree'),
				('parallelhashgrid', 'Parallel Hash Grid', 'parallelhashgrid'),
				('hybridhashgrid', 'Hybrid Hash Grid', 'hybridhashgrid'),
			],
			'save_in_preset': True
		},
		{
			'type': 'float',
			'attr': 'parallelhashgridspare',
			'name': 'Parallel Hash Grid Spare',
			'description': 'Higher values are faster but can use more memory',
			'default': 1.0,
			'save_in_preset': True
		},
		{
			'type': 'enum',
			'attr': 'pixelsampler',
			'name': 'Pixel sampler',
			'default': 'hilbert',
			'description': 'Sampling pattern used during the eye pass',
			'items': [
				('linear', 'Linear', 'Scan top-to-bottom, one pixel line at a time'),
				('tile', 'Tile', 'Scan in 32x32 blocks'),
				('vegas', 'Vegas', 'Random sample distribution'),
				('hilbert', 'Hilbert', 'Scan in a hilbert curve'),
			],
			'save_in_preset': True
		},
		{
			'type': 'enum',
			'attr': 'photonsampler',
			'name': 'Photon sampler',
			'default': 'halton',
			'description': 'Sampling method for photons',
			'items': [
				('amc', 'Adaptive Markov Chain', 'Use adapative markov chain monte carlo sampling'),
				('halton', 'Halton', 'Use a permuted halton sequence'),
			],
			'save_in_preset': True
		},
		#SPPM direct light sampling is a seperate parameter from Path's, due to the need for a different default and tooltip
		{
			'type': 'bool',
			'attr': 'sppmdirectlight',
			'name': 'Direct Light Sampling',
			'description': 'Use direct light sampling during the eye pass. Can improve efficiency with simple lighting',
			'default': False,
			'save_in_preset': True
		},
		{
			'type': 'int',
			'attr': 'wavelengthstratificationpasses',
			'name': 'Wavelength Stratification Passes',
			'description': 'Use non-random wavelengths for this many passes. Can help with wierd initial coloration due to unsampled wavelengths',
			'default': 8,
			'min': 0,
			'max': 64,
			'save_in_preset': True
		},
		{
			'type': 'bool',
			'attr': 'useproba',
			'name': 'Use PPM Probability',
			'description': 'Use PPM probability for search radius reduction.',
			'default': False,
			'save_in_preset': True
		},
	]
	
	def api_output(self, scene=None):
		'''
		Format this class's members into a LuxRender ParamSet
		
		Returns tuple
		'''
		
		params = ParamSet()
		
		#Check to make sure all settings are correct when hybrid is selected. Keep this up to date as hybrid gets new options in 0.9
		
		if scene.luxrender_rendermode.renderer == 'hybrid':
			#Check each integrator seperately so they don't mess with each other!
			if self.surfaceintegrator == 'path' and self.advanced == True:
				if self.lightstrategy not in ('one', 'all', 'auto'):
					LuxLog('Incompatible lightstrategy for Hybrid Path (use "auto", "all", or "one").')
					raise Exception('Incompatible render settings')
			if self.surfaceintegrator == 'bidirectional':
				if self.lightstrategy != ('one'):
					LuxLog('Incompatible lightstrategy for Hybrid Bidir (use "one").')
					raise Exception('Incompatible render settings')
		
		#Exphotonmap is not compatible with light groups, warn here instead of light export code so this warning only shows once instead of per lamp
		if scene.luxrender_lightgroups.ignore == False and self.surfaceintegrator == 'exphotonmap':
			LuxLog('WARNING: Ex-Photon Map does not support light groups, exporting all lights in the default group.')
				
		#Safety checks for settings end here
		
		if self.surfaceintegrator == 'bidirectional':
			params.add_integer('eyedepth', self.eyedepth) \
				  .add_integer('lightdepth', self.lightdepth)
			if self.advanced:
				params.add_float('eyerrthreshold', self.eyerrthreshold) \
					  .add_float('lightrrthreshold', self.lightrrthreshold)
		
		if self.surfaceintegrator == 'directlighting':
			params.add_integer('maxdepth', self.maxdepth) \
			
		if self.surfaceintegrator == 'sppm':
			params.add_integer('maxeyedepth', self.maxeyedepth) \
				  .add_integer('maxphotondepth', self.maxphotondepth) \
				  .add_integer('photonperpass', self.photonperpass) \
 				  .add_float('startradius', self.startradius) \
				  .add_float('alpha', self.alpha) \
				  .add_bool('includeenvironment', self.includeenvironment) \
				  .add_bool('directlightsampling', self.sppmdirectlight)
			if self.advanced:
				params.add_float('glossythreshold', self.glossythreshold) \
					  .add_bool('useproba', self.useproba)\
					  .add_integer('wavelengthstratificationpasses', self.wavelengthstratificationpasses) \
					  .add_string('lookupaccel', self.lookupaccel) \
					  .add_float('parallelhashgridspare', self.parallelhashgridspare) \
					  .add_string('pixelsampler', self.pixelsampler) \
					  .add_string('photonsampler', self.photonsampler)
		
		if self.surfaceintegrator == 'distributedpath':
			params.add_integer('directsamples', self.directsamples) \
				  .add_integer('indirectsamples', self.indirectsamples) \
				  .add_integer('diffusereflectdepth', self.diffusereflectdepth) \
				  .add_integer('diffusereflectsamples', self.diffusereflectsamples) \
				  .add_integer('diffuserefractdepth', self.diffuserefractdepth) \
				  .add_integer('diffuserefractsamples', self.diffuserefractsamples) \
				  .add_integer('glossyreflectdepth', self.glossyreflectdepth) \
				  .add_integer('glossyreflectsamples', self.glossyreflectsamples) \
				  .add_integer('glossyrefractdepth', self.glossyrefractdepth) \
				  .add_integer('glossyrefractsamples', self.glossyrefractsamples) \
				  .add_integer('specularreflectdepth', self.specularreflectdepth) \
				  .add_integer('specularrefractdepth', self.specularrefractdepth)
			if self.advanced:
				params.add_bool('directsampleall', self.directsampleall) \
					  .add_bool('directdiffuse', self.directdiffuse) \
					  .add_bool('directglossy', self.directglossy) \
					  .add_bool('indirectsampleall', self.indirectsampleall) \
				  	  .add_bool('indirectdiffuse', self.indirectdiffuse) \
				  	  .add_bool('indirectglossy', self.indirectglossy) \
					  .add_bool('diffusereflectreject', self.diffusereflectreject) \
					  .add_float('diffusereflectreject_threshold', self.diffusereflectreject_threshold) \
				  	  .add_bool('diffuserefractreject', self.diffuserefractreject) \
				  	  .add_float('diffuserefractreject_threshold', self.diffuserefractreject_threshold) \
				  	  .add_bool('glossyreflectreject', self.glossyreflectreject) \
				  	  .add_float('glossyreflectreject_threshold', self.glossyreflectreject_threshold) \
				  	  .add_bool('glossyrefractreject', self.glossyrefractreject) \
				  	  .add_float('glossyrefractreject_threshold', self.glossyrefractreject_threshold)
		
		if self.surfaceintegrator == 'exphotonmap':
			params.add_integer('maxdepth', self.maxeyedepth) \
				  .add_integer('maxphotondepth', self.maxphotondepth) \
				  .add_integer('directphotons', self.directphotons) \
				  .add_integer('causticphotons', self.causticphotons) \
				  .add_integer('indirectphotons', self.indirectphotons) \
				  .add_integer('radiancephotons', self.radiancephotons) \
				  .add_integer('nphotonsused', self.nphotonsused) \
				  .add_float('maxphotondist', self.maxphotondist) \
				  .add_bool('finalgather', self.finalgather) \
				  .add_integer('finalgathersamples', self.finalgathersamples) \
				  .add_string('renderingmode', self.renderingmode) \
				  .add_float('gatherangle', self.gatherangle) \
				  .add_string('rrstrategy', self.rrstrategy) \
				  .add_float('rrcontinueprob', self.rrcontinueprob)
				  #Export maxeyedepth as maxdepth, since that is actually the switch the scene file accepts
			if self.advanced:
				params.add_float('distancethreshold', self.distancethreshold) \
					  .add_string('photonmapsfile', self.photonmapsfile) 
			if self.debugmode:
				params.add_bool('dbg_enabledirect', self.dbg_enabledirect) \
					  .add_bool('dbg_enableradiancemap', self.dbg_enableradiancemap) \
					  .add_bool('dbg_enableindircaustic', self.dbg_enableindircaustic) \
					  .add_bool('dbg_enableindirdiffuse', self.dbg_enableindirdiffuse) \
					  .add_bool('dbg_enableindirspecular', self.dbg_enableindirspecular)
		
		if self.surfaceintegrator == 'igi':
			params.add_integer('nsets', self.nsets) \
				  .add_integer('nlights', self.nlights) \
				  .add_integer('maxdepth', self.maxdepth) \
				  .add_float('mindist', self.mindist)
		
		if self.surfaceintegrator == 'path':
			params.add_integer('maxdepth', self.maxdepth) \
				  .add_float('rrcontinueprob', self.rrcontinueprob) \
				  .add_string('rrstrategy', self.rrstrategy) \
				  .add_bool('includeenvironment', self.includeenvironment) \
				  .add_bool('directlightsampling', self.directlightsampling) \
				  .add_integer('shadowraycount', self.shadowraycount)
		
		if self.advanced and self.surfaceintegrator != 'sppm':
			params.add_string('lightstrategy', self.lightstrategy) \
		
		return self.surfaceintegrator, params